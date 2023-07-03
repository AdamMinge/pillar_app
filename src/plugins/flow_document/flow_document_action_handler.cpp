/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_action_handler.h"

#include "flow_document/command/add_remove_layer.h"
#include "flow_document/command/change_layer.h"
#include "flow_document/command/duplicate_layer.h"
#include "flow_document/command/raise_lower_layer.h"
#include "flow_document/event/layer_change_event.h"
#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/factory/layer_factory.h"
#include "flow_document/flow/factory/node_factory.h"
#include "flow_document/flow/factory/object_factory.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer_iterator.h"
#include "flow_document/flow/node_layer.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QStack>
/* ----------------------------------- Egnite ------------------------------- */
#include <egnite/action_manager.h>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/action/action.h>
#include <utils/pointer_cast/unique_ptr_cast.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

namespace {

[[nodiscard]] bool moreVisible(const QList<Layer*> layers) {
  auto count_of_visible =
      std::count_if(layers.cbegin(), layers.cend(),
                    [](const auto layer) { return layer->isVisible(); });

  return count_of_visible > (layers.count() - count_of_visible);
}

[[nodiscard]] bool moreLocked(const QList<Layer*> layers) {
  auto count_of_locked =
      std::count_if(layers.cbegin(), layers.cend(),
                    [](const auto layer) { return layer->isLocked(); });

  return count_of_locked > (layers.count() - count_of_locked);
}

[[nodiscard]] bool canRaiseLayers(FlowDocument* document,
                                  const QList<Layer*> layers) {
  if (layers.empty()) return false;

  auto root = document->getFlow()->getRootLayer();
  auto most_top_layer = root->at(root->size() - 1);

  return std::all_of(
      layers.cbegin(), layers.cend(),
      [most_top_layer](const auto layer) { return layer != most_top_layer; });
}

[[nodiscard]] bool canLowerLayers(FlowDocument* document,
                                  const QList<Layer*> layers) {
  if (layers.empty()) return false;

  auto root = document->getFlow()->getRootLayer();
  auto most_bottom_layer = root->at(0);

  return std::all_of(layers.cbegin(), layers.cend(),
                     [most_bottom_layer](const auto layer) {
                       return layer != most_bottom_layer;
                     });
}

}  // namespace

std::unique_ptr<FlowDocumentActionHandler>
    FlowDocumentActionHandler::m_instance =
        std::unique_ptr<FlowDocumentActionHandler>(nullptr);

FlowDocumentActionHandler& FlowDocumentActionHandler::getInstance() {
  if (!m_instance) m_instance.reset(new FlowDocumentActionHandler);

  return *m_instance;
}

void FlowDocumentActionHandler::deleteInstance() { m_instance.reset(nullptr); }

FlowDocumentActionHandler::FlowDocumentActionHandler() : m_document(nullptr) {
  initActions();
  connectActions();
  registerActions();
  updateActions();
  retranslateUi();
}

FlowDocumentActionHandler::~FlowDocumentActionHandler() { unregisterActions(); }

void FlowDocumentActionHandler::setDocument(FlowDocument* document) {
  if (m_document == document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::selectedLayersChanged, this,
               &FlowDocumentActionHandler::updateActions);
    disconnect(m_document, &FlowDocument::selectedNodesChanged, this,
               &FlowDocumentActionHandler::updateActions);
    disconnect(m_document, &FlowDocument::event, this,
               &FlowDocumentActionHandler::onEvent);
  }

  m_document = document;

  if (m_document) {
    connect(m_document, &FlowDocument::selectedLayersChanged, this,
            &FlowDocumentActionHandler::updateActions);
    connect(m_document, &FlowDocument::selectedNodesChanged, this,
            &FlowDocumentActionHandler::updateActions);
    connect(m_document, &FlowDocument::event, this,
            &FlowDocumentActionHandler::onEvent);
  }

  updateActions();
}

FlowDocument* FlowDocumentActionHandler::getDocument() const {
  return m_document;
}

QMenu* FlowDocumentActionHandler::getAddLayerMenu() const {
  return m_add_layer_menu.get();
}

QAction* FlowDocumentActionHandler::getRemoveLayerAction() const {
  return m_remove_layer;
}

QAction* FlowDocumentActionHandler::getRaiseLayerAction() const {
  return m_raise_layer;
}

QAction* FlowDocumentActionHandler::getLowerLayerAction() const {
  return m_lower_layer;
}

QAction* FlowDocumentActionHandler::getDuplicateLayerAction() const {
  return m_duplicate_layer;
}

QAction* FlowDocumentActionHandler::getShowHideOtherLayersAction() const {
  return m_show_hide_other_layers;
}

QAction* FlowDocumentActionHandler::getLockUnlockOtherLayersAction() const {
  return m_lock_unlock_other_layers;
}

QMenu* FlowDocumentActionHandler::getAddNodeMenu() const {
  return m_add_node_menu.get();
}

QAction* FlowDocumentActionHandler::getRemoveNodeAction() const {
  return m_remove_node;
}

QAction* FlowDocumentActionHandler::getMoveUpNodeAction() const {
  return m_move_up_node;
}

QAction* FlowDocumentActionHandler::getMoveDownNodeAction() const {
  return m_move_down_node;
}

QAction* FlowDocumentActionHandler::getDuplicateNodeAction() const {
  return m_duplicate_node;
}

void FlowDocumentActionHandler::addedObject(ObjectFactory* factory) {
  auto menu = menuForFactory(factory);
  if (!menu) return;

  auto factory_action = utils::createActionWithShortcut(QKeySequence{}, this);
  factory_action->setIcon(factory->getIcon());
  factory_action->setText(tr("&%1").arg(factory->getName()));
  factory_action->setWhatsThis(tr("Create %1").arg(factory->getName()));
  factory_action->setData(QVariant::fromValue(factory));

  connect(factory_action, &QAction::triggered,
          [this, factory]() { factory->addObject(m_document); });

  menu->addAction(factory_action);
}

void FlowDocumentActionHandler::removedObject(ObjectFactory* factory) {
  auto menu = menuForFactory(factory);
  if (!menu) return;

  for (auto action : menu->actions()) {
    auto action_factory = action->data().value<ObjectFactory*>();
    if (action_factory == factory) {
      menu->removeAction(action);
      action->deleteLater();
    }
  }
}

QMenu* FlowDocumentActionHandler::menuForFactory(ObjectFactory* factory) const {
  if (factory->getType() == NodeFactory::type) {
    return m_add_node_menu.get();
  } else if (factory->getType() == LayerFactory::type) {
    return m_add_layer_menu.get();
  }

  return nullptr;
}

void FlowDocumentActionHandler::onRemoveLayer() const {
  Q_ASSERT(m_document);

  const auto selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  auto entires = std::list<LayerEntry>{};
  for (auto selected_layer : selected_layers) {
    auto group_layer = selected_layer->getParent();
    entires.emplace_back(
        LayerEntry(group_layer, group_layer->indexOf(selected_layer)));
  }

  m_document->getUndoStack()->push(
      new RemoveLayers(m_document, std::move(entires)));
}

void FlowDocumentActionHandler::onRaiseLayer() const {
  Q_ASSERT(m_document);

  const auto& selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);
  Q_ASSERT(canRaiseLayers(m_document, selected_layers));

  m_document->getUndoStack()->push(
      new RaiseLayers(m_document, std::move(selected_layers)));
}

void FlowDocumentActionHandler::onLowerLayer() const {
  Q_ASSERT(m_document);

  const auto& selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);
  Q_ASSERT(canLowerLayers(m_document, selected_layers));

  m_document->getUndoStack()->push(
      new LowerLayers(m_document, std::move(selected_layers)));
}

void FlowDocumentActionHandler::onDuplicateLayer() const {
  Q_ASSERT(m_document);

  const auto& selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  m_document->getUndoStack()->push(
      new DuplicateLayers(m_document, selected_layers));
}

void FlowDocumentActionHandler::onShowHideOtherLayers() const {
  Q_ASSERT(m_document);

  const auto& selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  auto other_layers = getAllLayers(m_document, selected_layers);
  auto visible = !moreVisible(other_layers);

  m_document->getUndoStack()->push(
      new SetLayersVisible(m_document, other_layers, visible));
}

void FlowDocumentActionHandler::onLockUnlockOtherLayers() const {
  Q_ASSERT(m_document);

  const auto& selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  auto other_layers = getAllLayers(m_document, selected_layers);
  auto locked = !moreLocked(other_layers);

  m_document->getUndoStack()->push(
      new SetLayersLocked(m_document, other_layers, locked));
}

void FlowDocumentActionHandler::onRemoveNode() const {
  Q_ASSERT(m_document);

  const auto selected_nodes = m_document->getSelectedNodes();
  Q_ASSERT(selected_nodes.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onMoveUpNode() const {
  Q_ASSERT(m_document);

  const auto selected_nodes = m_document->getSelectedNodes();
  Q_ASSERT(selected_nodes.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onMoveDownNode() const {
  Q_ASSERT(m_document);

  const auto selected_nodes = m_document->getSelectedNodes();
  Q_ASSERT(selected_nodes.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onDuplicateNode() const {
  Q_ASSERT(m_document);

  const auto selected_nodes = m_document->getSelectedNodes();
  Q_ASSERT(selected_nodes.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onEvent(const ChangeEvent& event) {
  if (event.getType() == LayerEvent::type ||
      event.getType() == NodeEvent::type) {
    updateActions();
  }
}

void FlowDocumentActionHandler::initActions() {
  m_add_layer_menu.reset(new QMenu());
  m_remove_layer = utils::createActionWithShortcut(QKeySequence{}, this);
  m_raise_layer = utils::createActionWithShortcut(QKeySequence{}, this);
  m_lower_layer = utils::createActionWithShortcut(QKeySequence{}, this);
  m_duplicate_layer = utils::createActionWithShortcut(QKeySequence{}, this);
  m_show_hide_other_layers =
      utils::createActionWithShortcut(QKeySequence{}, this);
  m_lock_unlock_other_layers =
      utils::createActionWithShortcut(QKeySequence{}, this);

  m_add_node_menu.reset(new QMenu());
  m_remove_node = utils::createActionWithShortcut(QKeySequence{}, this);
  m_move_up_node = utils::createActionWithShortcut(QKeySequence{}, this);
  m_move_down_node = utils::createActionWithShortcut(QKeySequence{}, this);
  m_duplicate_node = utils::createActionWithShortcut(QKeySequence{}, this);

  m_add_layer_menu->setIcon(QIcon(icons::x16::Add));
  m_remove_layer->setIcon(QIcon(icons::x16::Remove));
  m_raise_layer->setIcon(QIcon(icons::x16::Up));
  m_lower_layer->setIcon(QIcon(icons::x16::Down));
  m_duplicate_layer->setIcon(QIcon(icons::x16::Duplicate));
  m_show_hide_other_layers->setIcon(QIcon(icons::x16::ShowHideOthers));
  m_lock_unlock_other_layers->setIcon(QIcon(icons::x16::Locked));

  m_add_node_menu->setIcon(QIcon(icons::x16::Add));
  m_remove_node->setIcon(QIcon(icons::x16::Remove));
  m_move_up_node->setIcon(QIcon(icons::x16::Up));
  m_move_down_node->setIcon(QIcon(icons::x16::Down));
  m_duplicate_node->setIcon(QIcon(icons::x16::Duplicate));
}

void FlowDocumentActionHandler::connectActions() {
  connect(m_remove_layer, &QAction::triggered, this,
          &FlowDocumentActionHandler::onRemoveLayer);
  connect(m_raise_layer, &QAction::triggered, this,
          &FlowDocumentActionHandler::onRaiseLayer);
  connect(m_lower_layer, &QAction::triggered, this,
          &FlowDocumentActionHandler::onLowerLayer);
  connect(m_duplicate_layer, &QAction::triggered, this,
          &FlowDocumentActionHandler::onDuplicateLayer);
  connect(m_show_hide_other_layers, &QAction::triggered, this,
          &FlowDocumentActionHandler::onShowHideOtherLayers);
  connect(m_lock_unlock_other_layers, &QAction::triggered, this,
          &FlowDocumentActionHandler::onLockUnlockOtherLayers);
  connect(m_remove_node, &QAction::triggered, this,
          &FlowDocumentActionHandler::onRemoveNode);
  connect(m_move_up_node, &QAction::triggered, this,
          &FlowDocumentActionHandler::onMoveUpNode);
  connect(m_move_down_node, &QAction::triggered, this,
          &FlowDocumentActionHandler::onMoveDownNode);
  connect(m_duplicate_node, &QAction::triggered, this,
          &FlowDocumentActionHandler::onDuplicateNode);
}

void FlowDocumentActionHandler::updateActions() {
  const auto has_document = m_document != nullptr;
  auto any_selected_layers = false;
  auto any_not_selected_layers = false;
  auto any_selected_nodes = false;
  auto can_raise_layers = false;
  auto can_lower_layers = false;

  if (has_document) {
    const auto& selected_layers = m_document->getSelectedLayers();
    const auto& selected_nodes = m_document->getSelectedNodes();
    const auto& not_selected_layers = getAllLayers(m_document, selected_layers);

    any_selected_layers = selected_layers.size() > 0;
    any_selected_nodes = selected_nodes.size() > 0;
    any_not_selected_layers = not_selected_layers.size() > 0;

    can_raise_layers = canRaiseLayers(m_document, selected_layers);
    can_lower_layers = canLowerLayers(m_document, selected_layers);
  }

  m_remove_layer->setEnabled(any_selected_layers);
  m_raise_layer->setEnabled(can_raise_layers);
  m_lower_layer->setEnabled(can_lower_layers);
  m_duplicate_layer->setEnabled(any_selected_layers);
  m_show_hide_other_layers->setEnabled(any_selected_layers &&
                                       any_not_selected_layers);
  m_lock_unlock_other_layers->setEnabled(any_selected_layers &&
                                         any_not_selected_layers);

  m_remove_node->setEnabled(any_selected_nodes);
  m_move_up_node->setEnabled(any_selected_nodes);
  m_move_down_node->setEnabled(any_selected_nodes);
  m_duplicate_node->setEnabled(any_selected_nodes);
}

void FlowDocumentActionHandler::retranslateUi() {
  m_add_layer_menu->setTitle(tr("&New"));
  m_add_layer_menu->setWhatsThis(tr("New"));

  m_remove_layer->setText(tr("&Remove Layers"));
  m_remove_layer->setWhatsThis(tr("Remove Selected Layers"));

  m_raise_layer->setText(tr("&Raise Layers"));
  m_raise_layer->setWhatsThis(tr("Raise Selected Layers"));

  m_lower_layer->setText(tr("&Lower Layers"));
  m_lower_layer->setWhatsThis(tr("Lower Selected Layers"));

  m_duplicate_layer->setText(tr("&Duplicate Layers"));
  m_duplicate_layer->setWhatsThis(tr("Duplicate Selected Layers"));

  m_show_hide_other_layers->setText(tr("Show/&Hide Layers"));
  m_show_hide_other_layers->setWhatsThis(tr("Show/Hide Selected Layers"));

  m_lock_unlock_other_layers->setText(tr("Lock/&Unlock Layers"));
  m_lock_unlock_other_layers->setWhatsThis(tr("Lock/Unlock Selected Layers"));

  m_add_node_menu->setTitle(tr("&New"));
  m_add_node_menu->setWhatsThis(tr("New"));

  m_remove_node->setText(tr("&Remove Nodes"));
  m_remove_node->setWhatsThis(tr("Remove Selected Nodes"));

  m_move_up_node->setText(tr("&Move Up Nodes"));
  m_move_up_node->setWhatsThis(tr("Move Up Selected Nodes"));

  m_move_down_node->setText(tr("&Move Down Nodes"));
  m_move_down_node->setWhatsThis(tr("Move Down Selected Nodes"));

  m_duplicate_node->setText(tr("&Duplicate Nodes"));
  m_duplicate_node->setWhatsThis(tr("Duplicate Selected Nodes"));
}

void FlowDocumentActionHandler::registerActions() {
  auto& action_manager = egnite::ActionManager::getInstance();
  action_manager.registerAction(m_remove_layer, "remove_layer");
  action_manager.registerAction(m_raise_layer, "raise_layer");
  action_manager.registerAction(m_lower_layer, "lower_layer");
  action_manager.registerAction(m_duplicate_layer, "duplicate_layer");
  action_manager.registerAction(m_show_hide_other_layers,
                                "show_hide_other_layers");
  action_manager.registerAction(m_lock_unlock_other_layers,
                                "lock_unlock_other_layers");
  action_manager.registerAction(m_remove_node, "remove_node");
  action_manager.registerAction(m_move_up_node, "move_up_node");
  action_manager.registerAction(m_move_down_node, "move_down_node");
  action_manager.registerAction(m_duplicate_node, "duplicate_node");
}

void FlowDocumentActionHandler::unregisterActions() {
  auto& action_manager = egnite::ActionManager::getInstance();
  action_manager.unregisterAction(m_remove_layer, "remove_layer");
  action_manager.unregisterAction(m_raise_layer, "raise_layer");
  action_manager.unregisterAction(m_lower_layer, "lower_layer");
  action_manager.unregisterAction(m_duplicate_layer, "duplicate_layer");
  action_manager.unregisterAction(m_show_hide_other_layers,
                                  "show_hide_other_layers");
  action_manager.unregisterAction(m_lock_unlock_other_layers,
                                  "lock_unlock_other_layers");
  action_manager.unregisterAction(m_remove_node, "remove_node");
  action_manager.unregisterAction(m_move_up_node, "move_up_node");
  action_manager.unregisterAction(m_move_down_node, "move_down_node");
  action_manager.unregisterAction(m_duplicate_node, "duplicate_node");
}

}  // namespace flow_document