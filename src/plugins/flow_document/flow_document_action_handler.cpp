/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_action_handler.h"

#include "flow_document/command/add_remove_connection.h"
#include "flow_document/command/add_remove_layer.h"
#include "flow_document/command/add_remove_node.h"
#include "flow_document/command/change_layer.h"
#include "flow_document/command/duplicate_layer.h"
#include "flow_document/command/duplicate_node.h"
#include "flow_document/command/raise_lower_layer.h"
#include "flow_document/command/raise_lower_node.h"
#include "flow_document/component/connections/new_connections_dialog.h"
#include "flow_document/event/connection_change_event.h"
#include "flow_document/event/layer_change_event.h"
#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/connection_layer.h"
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

/* ----------------------------------- Utils -------------------------------- */

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

[[nodiscard]] bool canRaiseNodes(FlowDocument* document,
                                 const QList<Node*> nodes) {
  if (nodes.empty()) return false;

  return std::all_of(nodes.cbegin(), nodes.cend(), [](const auto node) {
    auto node_layer = node->getParent();
    if (!node_layer) return false;

    auto most_top_node = node_layer->at(node_layer->size() - 1);
    return node != most_top_node;
  });
}

[[nodiscard]] bool canLowerNodes(FlowDocument* document,
                                 const QList<Node*> nodes) {
  if (nodes.empty()) return false;

  return std::all_of(nodes.cbegin(), nodes.cend(), [](const auto node) {
    auto node_layer = node->getParent();
    if (!node_layer) return false;

    auto most_bottom_node = node_layer->at(0);
    return node != most_bottom_node;
  });
}

}  // namespace

/* -------------------------- FlowDocumentActionHandler --------------------- */

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
    disconnect(m_document, &FlowDocument::selectedConnectionsChanged, this,
               &FlowDocumentActionHandler::updateActions);
    disconnect(m_document, &FlowDocument::currentLayerChanged, this,
               &FlowDocumentActionHandler::updateActions);
    disconnect(m_document, &FlowDocument::currentNodeChanged, this,
               &FlowDocumentActionHandler::updateActions);
    disconnect(m_document, &FlowDocument::currentConnectionChanged, this,
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
    connect(m_document, &FlowDocument::selectedConnectionsChanged, this,
            &FlowDocumentActionHandler::updateActions);
    connect(m_document, &FlowDocument::currentLayerChanged, this,
            &FlowDocumentActionHandler::updateActions);
    connect(m_document, &FlowDocument::currentNodeChanged, this,
            &FlowDocumentActionHandler::updateActions);
    connect(m_document, &FlowDocument::currentConnectionChanged, this,
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

QAction* FlowDocumentActionHandler::getRaiseNodeAction() const {
  return m_raise_node;
}

QAction* FlowDocumentActionHandler::getLowerNodeAction() const {
  return m_lower_node;
}

QAction* FlowDocumentActionHandler::getDuplicateNodeAction() const {
  return m_duplicate_node;
}

QAction* FlowDocumentActionHandler::getAddConnectionAction() const {
  return m_add_connection;
}

QAction* FlowDocumentActionHandler::getRemoveConnectionAction() const {
  return m_remove_connection;
}

QToolButton* FlowDocumentActionHandler::createAddLayerButton() const {
  auto new_layer_button = new QToolButton();
  new_layer_button->setPopupMode(QToolButton::InstantPopup);
  new_layer_button->setMenu(getAddLayerMenu());
  new_layer_button->setIcon(getAddLayerMenu()->icon());

  connect(this, &FlowDocumentActionHandler::onUpdateActions,
          [new_layer_button]() {
            auto menu = new_layer_button->menu();
            new_layer_button->setEnabled(menu->isEnabled());
          });

  return new_layer_button;
}

QToolButton* FlowDocumentActionHandler::createAddNodeButton() const {
  auto new_node_button = new QToolButton();
  new_node_button->setPopupMode(QToolButton::InstantPopup);
  new_node_button->setMenu(getAddNodeMenu());
  new_node_button->setIcon(getAddNodeMenu()->icon());

  connect(this, &FlowDocumentActionHandler::onUpdateActions,
          [new_node_button]() {
            auto menu = new_node_button->menu();
            new_node_button->setEnabled(menu->isEnabled());
          });

  return new_node_button;
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

  auto entires = std::list<NodeEntry>{};
  for (auto selected_node : selected_nodes) {
    auto node_layer = selected_node->getParent();
    entires.emplace_back(
        NodeEntry(node_layer, node_layer->indexOf(selected_node)));
  }

  m_document->getUndoStack()->push(
      new RemoveNodes(m_document, std::move(entires)));
}

void FlowDocumentActionHandler::onRaiseNode() const {
  Q_ASSERT(m_document);

  const auto selected_nodes = m_document->getSelectedNodes();
  Q_ASSERT(selected_nodes.size() > 0);
  Q_ASSERT(canRaiseNodes(m_document, selected_nodes));

  m_document->getUndoStack()->push(
      new RaiseNodes(m_document, std::move(selected_nodes)));
}

void FlowDocumentActionHandler::onLowerNode() const {
  Q_ASSERT(m_document);

  const auto selected_nodes = m_document->getSelectedNodes();
  Q_ASSERT(selected_nodes.size() > 0);
  Q_ASSERT(canLowerNodes(m_document, selected_nodes));

  m_document->getUndoStack()->push(
      new LowerNodes(m_document, std::move(selected_nodes)));
}

void FlowDocumentActionHandler::onDuplicateNode() const {
  Q_ASSERT(m_document);

  const auto selected_nodes = m_document->getSelectedNodes();
  Q_ASSERT(selected_nodes.size() > 0);

  m_document->getUndoStack()->push(
      new DuplicateNodes(m_document, selected_nodes));
}

void FlowDocumentActionHandler::onAddConnection() const {
  Q_ASSERT(m_document);

  if (!m_new_connections_dialog) {
    m_new_connections_dialog = new NewConnectionsDialog(m_document);
  }

  m_new_connections_dialog->setAttribute(Qt::WA_DeleteOnClose);
  m_new_connections_dialog->setConnectionLayer(
      static_cast<ConnectionLayer*>(m_document->getCurrentLayer()));
  m_new_connections_dialog->exec();
}

void FlowDocumentActionHandler::onRemoveConnection() const {
  Q_ASSERT(m_document);

  const auto selected_connections = m_document->getSelectedConnections();
  Q_ASSERT(selected_connections.size() > 0);

  auto entires = std::list<ConnectionEntry>{};
  for (auto selected_connection : selected_connections) {
    auto connection_layer = selected_connection->getParent();
    entires.emplace_back(ConnectionEntry(
        connection_layer, connection_layer->indexOf(selected_connection)));
  }

  m_document->getUndoStack()->push(
      new RemoveConnections(m_document, std::move(entires)));
}

void FlowDocumentActionHandler::onEvent(const ChangeEvent& event) {
  if (event.getType() == LayerEvent::type ||
      event.getType() == NodeEvent::type ||
      event.getType() == ConnectionEvent::type) {
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
  m_raise_node = utils::createActionWithShortcut(QKeySequence{}, this);
  m_lower_node = utils::createActionWithShortcut(QKeySequence{}, this);
  m_duplicate_node = utils::createActionWithShortcut(QKeySequence{}, this);

  m_add_connection = utils::createActionWithShortcut(QKeySequence{}, this);
  m_remove_connection = utils::createActionWithShortcut(QKeySequence{}, this);

  m_add_layer_menu->setIcon(QIcon(icons::x16::Add));
  m_remove_layer->setIcon(QIcon(icons::x16::Remove));
  m_raise_layer->setIcon(QIcon(icons::x16::Up));
  m_lower_layer->setIcon(QIcon(icons::x16::Down));
  m_duplicate_layer->setIcon(QIcon(icons::x16::Duplicate));
  m_show_hide_other_layers->setIcon(QIcon(icons::x16::ShowHideOthers));
  m_lock_unlock_other_layers->setIcon(QIcon(icons::x16::Locked));

  m_add_node_menu->setIcon(QIcon(icons::x16::Add));
  m_remove_node->setIcon(QIcon(icons::x16::Remove));
  m_raise_node->setIcon(QIcon(icons::x16::Up));
  m_lower_node->setIcon(QIcon(icons::x16::Down));
  m_duplicate_node->setIcon(QIcon(icons::x16::Duplicate));

  m_add_connection->setIcon(QIcon(icons::x16::Add));
  m_remove_connection->setIcon(QIcon(icons::x16::Remove));
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
  connect(m_raise_node, &QAction::triggered, this,
          &FlowDocumentActionHandler::onRaiseNode);
  connect(m_lower_node, &QAction::triggered, this,
          &FlowDocumentActionHandler::onLowerNode);
  connect(m_duplicate_node, &QAction::triggered, this,
          &FlowDocumentActionHandler::onDuplicateNode);

  connect(m_add_connection, &QAction::triggered, this,
          &FlowDocumentActionHandler::onAddConnection);
  connect(m_remove_connection, &QAction::triggered, this,
          &FlowDocumentActionHandler::onRemoveConnection);
}

void FlowDocumentActionHandler::updateActions() {
  const auto has_document = m_document != nullptr;
  auto any_selected_layers = false;
  auto any_not_selected_layers = false;
  auto any_selected_nodes = false;
  auto can_raise_layers = false;
  auto can_lower_layers = false;
  auto can_add_node = false;
  auto can_raise_nodes = false;
  auto can_lower_nodes = false;
  auto any_selected_connections = false;
  auto can_add_connection = false;

  if (has_document) {
    const auto& selected_layers = m_document->getSelectedLayers();
    const auto& selected_nodes = m_document->getSelectedNodes();
    const auto& selected_connections = m_document->getSelectedConnections();
    const auto& not_selected_layers = getAllLayers(m_document, selected_layers);
    const auto current_layer = m_document->getCurrentLayer();

    any_selected_layers = selected_layers.size() > 0;
    any_not_selected_layers = not_selected_layers.size() > 0;

    can_raise_layers = canRaiseLayers(m_document, selected_layers);
    can_lower_layers = canLowerLayers(m_document, selected_layers);

    can_add_node = current_layer && current_layer->isClassOrChild<NodeLayer>();
    any_selected_nodes = selected_nodes.size() > 0;

    can_raise_nodes = canRaiseNodes(m_document, selected_nodes);
    can_lower_nodes = canLowerNodes(m_document, selected_nodes);

    can_add_connection =
        current_layer && current_layer->isClassOrChild<ConnectionLayer>();
    any_selected_connections = selected_connections.size() > 0;
  }

  m_remove_layer->setEnabled(any_selected_layers);
  m_raise_layer->setEnabled(can_raise_layers);
  m_lower_layer->setEnabled(can_lower_layers);
  m_duplicate_layer->setEnabled(any_selected_layers);
  m_show_hide_other_layers->setEnabled(any_selected_layers &&
                                       any_not_selected_layers);
  m_lock_unlock_other_layers->setEnabled(any_selected_layers &&
                                         any_not_selected_layers);

  m_add_node_menu->setEnabled(can_add_node);
  m_remove_node->setEnabled(any_selected_nodes);
  m_raise_node->setEnabled(can_raise_nodes);
  m_lower_node->setEnabled(can_lower_nodes);
  m_duplicate_node->setEnabled(any_selected_nodes);

  m_add_connection->setEnabled(can_add_connection);
  m_remove_connection->setEnabled(any_selected_connections);

  Q_EMIT onUpdateActions();
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

  m_raise_node->setText(tr("&Raise Nodes"));
  m_raise_node->setWhatsThis(tr("Raise Selected Nodes"));

  m_lower_node->setText(tr("&Lower Nodes"));
  m_lower_node->setWhatsThis(tr("Lower Selected Nodes"));

  m_duplicate_node->setText(tr("&Duplicate Nodes"));
  m_duplicate_node->setWhatsThis(tr("Duplicate Selected Nodes"));

  m_add_connection->setText(tr("&New Connection..."));
  m_add_connection->setWhatsThis(tr("New Connection"));

  m_remove_connection->setText(tr("&Remove Connection"));
  m_remove_connection->setWhatsThis(tr("Remove Selected Connection"));
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
  action_manager.registerAction(m_raise_node, "raise_node");
  action_manager.registerAction(m_lower_node, "lower_node");
  action_manager.registerAction(m_duplicate_node, "duplicate_node");

  action_manager.registerAction(m_remove_connection, "remove_connection");
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
  action_manager.unregisterAction(m_raise_node, "raise_node");
  action_manager.unregisterAction(m_lower_node, "lower_node");
  action_manager.unregisterAction(m_duplicate_node, "duplicate_node");

  action_manager.unregisterAction(m_remove_connection, "remove_connection");
}

}  // namespace flow_document