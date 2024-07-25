/* ----------------------------------- Local -------------------------------- */
#include "flow/document/action_handler.h"

#include "flow/document/command/add_remove_connection.h"
#include "flow/document/command/add_remove_layer.h"
#include "flow/document/command/add_remove_node.h"
#include "flow/document/command/change_layer.h"
#include "flow/document/command/duplicate_layer.h"
#include "flow/document/command/duplicate_node.h"
#include "flow/document/command/raise_lower_layer.h"
#include "flow/document/command/raise_lower_node.h"
#include "flow/document/component/connections/new_connections_dialog.h"
#include "flow/document/document.h"
#include "flow/document/event/connection_change_event.h"
#include "flow/document/event/layer_change_event.h"
#include "flow/document/event/node_change_event.h"
#include "flow/document/flow/factory/layer_factory.h"
#include "flow/document/flow/factory/node_factory.h"
#include "flow/document/flow/factory/object_factory.h"
#include "flow/document/flow/flow.h"
#include "flow/document/flow/group_layer.h"
#include "flow/document/flow/layer_iterator.h"
#include "flow/document/flow/node_layer.h"
#include "flow/document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QStack>
/* --------------------------------- Standard ------------------------------- */
#include <set>
/* ----------------------------------- Pillar ------------------------------- */
#include <pillar/action_manager.h>
#include <pillar/command/group_command.h>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/action/action.h>
#include <qtils/pointer/unique_ptr_cast.h>
/* -------------------------------------------------------------------------- */

namespace flow {

namespace {

/* ----------------------------------- Qtils -------------------------------- */

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
  auto most_top_layer = root->at(root->count() - 1);

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

    auto most_top_node = node_layer->nodeAt(node_layer->nodesCount() - 1);
    return node != most_top_node;
  });
}

[[nodiscard]] bool canLowerNodes(FlowDocument* document,
                                 const QList<Node*> nodes) {
  if (nodes.empty()) return false;

  return std::all_of(nodes.cbegin(), nodes.cend(), [](const auto node) {
    auto node_layer = node->getParent();
    if (!node_layer) return false;

    auto most_bottom_node = node_layer->nodeAt(0);
    return node != most_bottom_node;
  });
}

}  // namespace

/* -------------------------- ActionHandler --------------------- */

std::unique_ptr<ActionHandler> ActionHandler::m_instance =
    std::unique_ptr<ActionHandler>(nullptr);

ActionHandler& ActionHandler::getInstance() {
  if (!m_instance) m_instance.reset(new ActionHandler);

  return *m_instance;
}

void ActionHandler::deleteInstance() { m_instance.reset(nullptr); }

ActionHandler::ActionHandler() : m_document(nullptr) {
  initActions();
  connectActions();
  registerActions();
  updateActions();
  retranslateUi();
}

ActionHandler::~ActionHandler() { unregisterActions(); }

void ActionHandler::setDocument(FlowDocument* document) {
  if (m_document == document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::selectedLayersChanged, this,
               &ActionHandler::updateActions);
    disconnect(m_document, &FlowDocument::selectedNodesChanged, this,
               &ActionHandler::updateActions);
    disconnect(m_document, &FlowDocument::selectedConnectionsChanged, this,
               &ActionHandler::updateActions);
    disconnect(m_document, &FlowDocument::currentLayerChanged, this,
               &ActionHandler::updateActions);
    disconnect(m_document, &FlowDocument::currentNodeChanged, this,
               &ActionHandler::updateActions);
    disconnect(m_document, &FlowDocument::currentConnectionChanged, this,
               &ActionHandler::updateActions);
    disconnect(m_document, &FlowDocument::event, this, &ActionHandler::onEvent);
  }

  m_document = document;

  if (m_document) {
    connect(m_document, &FlowDocument::selectedLayersChanged, this,
            &ActionHandler::updateActions);
    connect(m_document, &FlowDocument::selectedNodesChanged, this,
            &ActionHandler::updateActions);
    connect(m_document, &FlowDocument::selectedConnectionsChanged, this,
            &ActionHandler::updateActions);
    connect(m_document, &FlowDocument::currentLayerChanged, this,
            &ActionHandler::updateActions);
    connect(m_document, &FlowDocument::currentNodeChanged, this,
            &ActionHandler::updateActions);
    connect(m_document, &FlowDocument::currentConnectionChanged, this,
            &ActionHandler::updateActions);
    connect(m_document, &FlowDocument::event, this, &ActionHandler::onEvent);
  }

  updateActions();
}

FlowDocument* ActionHandler::getDocument() const { return m_document; }

QMenu* ActionHandler::getAddLayerMenu() const { return m_add_layer_menu.get(); }

QAction* ActionHandler::getRemoveLayerAction() const { return m_remove_layer; }

QAction* ActionHandler::getRaiseLayerAction() const { return m_raise_layer; }

QAction* ActionHandler::getLowerLayerAction() const { return m_lower_layer; }

QAction* ActionHandler::getDuplicateLayerAction() const {
  return m_duplicate_layer;
}

QAction* ActionHandler::getShowHideOtherLayersAction() const {
  return m_show_hide_other_layers;
}

QAction* ActionHandler::getLockUnlockOtherLayersAction() const {
  return m_lock_unlock_other_layers;
}

QMenu* ActionHandler::getAddNodeMenu() const { return m_add_node_menu.get(); }

QAction* ActionHandler::getRemoveNodeAction() const { return m_remove_node; }

QAction* ActionHandler::getRaiseNodeAction() const { return m_raise_node; }

QAction* ActionHandler::getLowerNodeAction() const { return m_lower_node; }

QAction* ActionHandler::getDuplicateNodeAction() const {
  return m_duplicate_node;
}

QAction* ActionHandler::getAddConnectionAction() const {
  return m_add_connection;
}

QAction* ActionHandler::getRemoveConnectionAction() const {
  return m_remove_connection;
}

QToolButton* ActionHandler::createAddLayerButton() const {
  auto new_layer_button = new QToolButton();
  new_layer_button->setPopupMode(QToolButton::InstantPopup);
  new_layer_button->setMenu(getAddLayerMenu());
  new_layer_button->setIcon(getAddLayerMenu()->icon());

  connect(this, &ActionHandler::onUpdateActions, [new_layer_button]() {
    auto menu = new_layer_button->menu();
    new_layer_button->setEnabled(menu->isEnabled());
  });

  return new_layer_button;
}

QToolButton* ActionHandler::createAddNodeButton() const {
  auto new_node_button = new QToolButton();
  new_node_button->setPopupMode(QToolButton::InstantPopup);
  new_node_button->setMenu(getAddNodeMenu());
  new_node_button->setIcon(getAddNodeMenu()->icon());

  connect(this, &ActionHandler::onUpdateActions, [new_node_button]() {
    auto menu = new_node_button->menu();
    new_node_button->setEnabled(menu->isEnabled());
  });

  return new_node_button;
}

void ActionHandler::addedObject(ObjectFactory* factory) {
  auto menu = menuForFactory(factory);
  if (!menu) return;

  auto factory_action = qtils::createActionWithShortcut(QKeySequence{}, this);
  factory_action->setIcon(factory->getIcon());
  factory_action->setText(tr("&%1").arg(factory->getName()));
  factory_action->setWhatsThis(tr("Create %1").arg(factory->getName()));
  factory_action->setData(QVariant::fromValue(factory));

  connect(factory_action, &QAction::triggered,
          [this, factory]() { factory->addObject(m_document); });

  menu->addAction(factory_action);
}

void ActionHandler::removedObject(ObjectFactory* factory) {
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

QMenu* ActionHandler::menuForFactory(ObjectFactory* factory) const {
  if (factory->getType() == NodeFactory::type) {
    return m_add_node_menu.get();
  } else if (factory->getType() == LayerFactory::type) {
    return m_add_layer_menu.get();
  }

  return nullptr;
}

void ActionHandler::onRemoveLayer() const {
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

void ActionHandler::onRaiseLayer() const {
  Q_ASSERT(m_document);

  const auto& selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);
  Q_ASSERT(canRaiseLayers(m_document, selected_layers));

  m_document->getUndoStack()->push(
      new RaiseLayers(m_document, std::move(selected_layers)));
}

void ActionHandler::onLowerLayer() const {
  Q_ASSERT(m_document);

  const auto& selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);
  Q_ASSERT(canLowerLayers(m_document, selected_layers));

  m_document->getUndoStack()->push(
      new LowerLayers(m_document, std::move(selected_layers)));
}

void ActionHandler::onDuplicateLayer() const {
  Q_ASSERT(m_document);

  const auto& selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  m_document->getUndoStack()->push(
      new DuplicateLayers(m_document, selected_layers));
}

void ActionHandler::onShowHideOtherLayers() const {
  Q_ASSERT(m_document);

  const auto& selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  auto other_layers = getAllLayers(m_document, selected_layers);
  auto visible = !moreVisible(other_layers);

  m_document->getUndoStack()->push(
      new SetLayersVisible(m_document, other_layers, visible));
}

void ActionHandler::onLockUnlockOtherLayers() const {
  Q_ASSERT(m_document);

  const auto& selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  auto other_layers = getAllLayers(m_document, selected_layers);
  auto locked = !moreLocked(other_layers);

  m_document->getUndoStack()->push(
      new SetLayersLocked(m_document, other_layers, locked));
}

void ActionHandler::onRemoveNode() const {
  Q_ASSERT(m_document);

  const auto selected_nodes = m_document->getSelectedNodes();
  Q_ASSERT(selected_nodes.size() > 0);

  auto node_entires = std::list<NodeEntry>{};
  auto connection_entires = std::list<ConnectionEntry>{};
  auto selected_connections = std::set<Connection*>{};

  for (auto selected_node : selected_nodes) {
    auto node_layer = selected_node->getParent();

    node_entires.emplace_back(
        NodeEntry(node_layer, node_layer->indexOfNode(selected_node)));

    auto node_connections = node_layer->getNodeConnections(selected_node);
    for (auto connection : node_connections) {
      if (!selected_connections.insert(connection).second) continue;

      connection_entires.emplace_back(ConnectionEntry(
          node_layer, node_layer->indexOfConnection(connection)));
    }
  }

  auto remove_connections_command =
      new RemoveConnections(m_document, std::move(connection_entires));
  auto remove_nodes_command =
      new RemoveNodes(m_document, std::move(node_entires));

  auto group_remove_nodes_command =
      new pillar::GroupCommand(remove_nodes_command->text());
  group_remove_nodes_command->addCommand(remove_connections_command);
  group_remove_nodes_command->addCommand(remove_nodes_command);

  m_document->getUndoStack()->push(group_remove_nodes_command);
}

void ActionHandler::onRaiseNode() const {
  Q_ASSERT(m_document);

  const auto selected_nodes = m_document->getSelectedNodes();
  Q_ASSERT(selected_nodes.size() > 0);
  Q_ASSERT(canRaiseNodes(m_document, selected_nodes));

  m_document->getUndoStack()->push(
      new RaiseNodes(m_document, std::move(selected_nodes)));
}

void ActionHandler::onLowerNode() const {
  Q_ASSERT(m_document);

  const auto selected_nodes = m_document->getSelectedNodes();
  Q_ASSERT(selected_nodes.size() > 0);
  Q_ASSERT(canLowerNodes(m_document, selected_nodes));

  m_document->getUndoStack()->push(
      new LowerNodes(m_document, std::move(selected_nodes)));
}

void ActionHandler::onDuplicateNode() const {
  Q_ASSERT(m_document);

  const auto selected_nodes = m_document->getSelectedNodes();
  Q_ASSERT(selected_nodes.size() > 0);

  m_document->getUndoStack()->push(
      new DuplicateNodes(m_document, selected_nodes));
}

void ActionHandler::onAddConnection() const {
  Q_ASSERT(m_document);

  if (!m_new_connections_dialog) {
    m_new_connections_dialog = new NewConnectionsDialog(m_document);
  }

  m_new_connections_dialog->setAttribute(Qt::WA_DeleteOnClose);
  m_new_connections_dialog->setNodeLayer(
      static_cast<NodeLayer*>(m_document->getCurrentLayer()));
  m_new_connections_dialog->exec();
}

void ActionHandler::onRemoveConnection() const {
  Q_ASSERT(m_document);

  const auto selected_connections = m_document->getSelectedConnections();
  Q_ASSERT(selected_connections.size() > 0);

  auto entires = std::list<ConnectionEntry>{};
  for (auto selected_connection : selected_connections) {
    auto connection_layer = selected_connection->getParent();
    entires.emplace_back(ConnectionEntry(
        connection_layer,
        connection_layer->indexOfConnection(selected_connection)));
  }

  m_document->getUndoStack()->push(
      new RemoveConnections(m_document, std::move(entires)));
}

void ActionHandler::onEvent(const ChangeEvent& event) {
  if (event.getType() == LayerEvent::type ||
      event.getType() == NodeEvent::type ||
      event.getType() == ConnectionEvent::type) {
    updateActions();
  }
}

void ActionHandler::initActions() {
  m_add_layer_menu.reset(new QMenu());
  m_remove_layer = qtils::createActionWithShortcut(QKeySequence{}, this);
  m_raise_layer = qtils::createActionWithShortcut(QKeySequence{}, this);
  m_lower_layer = qtils::createActionWithShortcut(QKeySequence{}, this);
  m_duplicate_layer = qtils::createActionWithShortcut(QKeySequence{}, this);
  m_show_hide_other_layers =
      qtils::createActionWithShortcut(QKeySequence{}, this);
  m_lock_unlock_other_layers =
      qtils::createActionWithShortcut(QKeySequence{}, this);

  m_add_node_menu.reset(new QMenu());
  m_remove_node = qtils::createActionWithShortcut(QKeySequence{}, this);
  m_raise_node = qtils::createActionWithShortcut(QKeySequence{}, this);
  m_lower_node = qtils::createActionWithShortcut(QKeySequence{}, this);
  m_duplicate_node = qtils::createActionWithShortcut(QKeySequence{}, this);

  m_add_connection = qtils::createActionWithShortcut(QKeySequence{}, this);
  m_remove_connection = qtils::createActionWithShortcut(QKeySequence{}, this);

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

void ActionHandler::connectActions() {
  connect(m_remove_layer, &QAction::triggered, this,
          &ActionHandler::onRemoveLayer);
  connect(m_raise_layer, &QAction::triggered, this,
          &ActionHandler::onRaiseLayer);
  connect(m_lower_layer, &QAction::triggered, this,
          &ActionHandler::onLowerLayer);
  connect(m_duplicate_layer, &QAction::triggered, this,
          &ActionHandler::onDuplicateLayer);
  connect(m_show_hide_other_layers, &QAction::triggered, this,
          &ActionHandler::onShowHideOtherLayers);
  connect(m_lock_unlock_other_layers, &QAction::triggered, this,
          &ActionHandler::onLockUnlockOtherLayers);

  connect(m_remove_node, &QAction::triggered, this,
          &ActionHandler::onRemoveNode);
  connect(m_raise_node, &QAction::triggered, this, &ActionHandler::onRaiseNode);
  connect(m_lower_node, &QAction::triggered, this, &ActionHandler::onLowerNode);
  connect(m_duplicate_node, &QAction::triggered, this,
          &ActionHandler::onDuplicateNode);

  connect(m_add_connection, &QAction::triggered, this,
          &ActionHandler::onAddConnection);
  connect(m_remove_connection, &QAction::triggered, this,
          &ActionHandler::onRemoveConnection);
}

void ActionHandler::updateActions() {
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
        current_layer && current_layer->isClassOrChild<NodeLayer>();
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

void ActionHandler::retranslateUi() {
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

void ActionHandler::registerActions() {
  auto& action_manager = pillar::ActionManager::getInstance();
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

void ActionHandler::unregisterActions() {
  auto& action_manager = pillar::ActionManager::getInstance();
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

}  // namespace flow