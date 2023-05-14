/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_action_handler.h"

#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ----------------------------------- Egnite ------------------------------- */
#include <egnite/action_manager.h>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/action/action.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

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
    disconnect(m_document, &FlowDocument::selectedObjectsChanged, this,
               &FlowDocumentActionHandler::updateActions);
  }

  m_document = document;

  if (m_document) {
    connect(m_document, &FlowDocument::selectedLayersChanged, this,
            &FlowDocumentActionHandler::updateActions);
    connect(m_document, &FlowDocument::selectedObjectsChanged, this,
            &FlowDocumentActionHandler::updateActions);
  }

  updateActions();
}

FlowDocument* FlowDocumentActionHandler::getDocument() const {
  return m_document;
}

QAction* FlowDocumentActionHandler::getAddGroupLayerAction() const {
  return m_add_group_layer;
}

QAction* FlowDocumentActionHandler::getAddNodeLayerAction() const {
  return m_add_node_layer;
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

QAction* FlowDocumentActionHandler::getRemoveObjectAction() const {
  return m_remove_object;
}

QAction* FlowDocumentActionHandler::getRaiseObjectAction() const {
  return m_raise_object;
}

QAction* FlowDocumentActionHandler::getLowerObjectAction() const {
  return m_lower_object;
}

QAction* FlowDocumentActionHandler::getDuplicateObjectAction() const {
  return m_duplicate_object;
}

QMenu* FlowDocumentActionHandler::createNewLayerMenu(QWidget* parent) const {
  auto menu = new QMenu(tr("&New"), parent);
  menu->setIcon(QIcon(icons::x16::Add));

  menu->addAction(m_add_group_layer);
  menu->addAction(m_add_node_layer);

  return menu;
}

void FlowDocumentActionHandler::onAddGroupLayer() const {
  Q_ASSERT(m_document);

  // TODO
}

void FlowDocumentActionHandler::onAddNodeLayer() const {
  Q_ASSERT(m_document);

  // TODO
}

void FlowDocumentActionHandler::onRemoveLayer() const {
  Q_ASSERT(m_document);

  const auto selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onRaiseLayer() const {
  Q_ASSERT(m_document);

  const auto selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onLowerLayer() const {
  Q_ASSERT(m_document);

  const auto selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onDuplicateLayer() const {
  Q_ASSERT(m_document);

  const auto selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onShowHideOtherLayers() const {
  Q_ASSERT(m_document);

  const auto selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onLockUnlockOtherLayers() const {
  Q_ASSERT(m_document);

  const auto selected_layers = m_document->getSelectedLayers();
  Q_ASSERT(selected_layers.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onRemoveObject() const {
  Q_ASSERT(m_document);

  const auto selected_objects = m_document->getSelectedObject();
  Q_ASSERT(selected_objects.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onRaiseObject() const {
  Q_ASSERT(m_document);

  const auto selected_objects = m_document->getSelectedObject();
  Q_ASSERT(selected_objects.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onLowerObject() const {
  Q_ASSERT(m_document);

  const auto selected_objects = m_document->getSelectedObject();
  Q_ASSERT(selected_objects.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::onDuplicateObject() const {
  Q_ASSERT(m_document);

  const auto selected_objects = m_document->getSelectedObject();
  Q_ASSERT(selected_objects.size() > 0);

  // TODO
}

void FlowDocumentActionHandler::initActions() {
  m_add_group_layer = utils::createActionWithShortcut(QKeySequence{}, this);
  m_add_node_layer = utils::createActionWithShortcut(QKeySequence{}, this);
  m_remove_layer = utils::createActionWithShortcut(QKeySequence{}, this);
  m_raise_layer = utils::createActionWithShortcut(QKeySequence{}, this);
  m_lower_layer = utils::createActionWithShortcut(QKeySequence{}, this);
  m_duplicate_layer = utils::createActionWithShortcut(QKeySequence{}, this);
  m_show_hide_other_layers =
      utils::createActionWithShortcut(QKeySequence{}, this);
  m_lock_unlock_other_layers =
      utils::createActionWithShortcut(QKeySequence{}, this);
  m_remove_object = utils::createActionWithShortcut(QKeySequence{}, this);
  m_raise_object = utils::createActionWithShortcut(QKeySequence{}, this);
  m_lower_object = utils::createActionWithShortcut(QKeySequence{}, this);
  m_duplicate_object = utils::createActionWithShortcut(QKeySequence{}, this);

  m_add_group_layer->setIcon(QIcon(icons::x16::GroupLayer));
  m_add_node_layer->setIcon(QIcon(icons::x16::NodeLayer));
  m_remove_layer->setIcon(QIcon(icons::x16::Remove));
  m_raise_layer->setIcon(QIcon(icons::x16::Up));
  m_lower_layer->setIcon(QIcon(icons::x16::Down));
  m_duplicate_layer->setIcon(QIcon(icons::x16::Duplicate));
  m_show_hide_other_layers->setIcon(QIcon(icons::x16::ShowHideOthers));
  m_lock_unlock_other_layers->setIcon(QIcon(icons::x16::Locked));
  m_remove_object->setIcon(QIcon(icons::x16::Remove));
  m_raise_object->setIcon(QIcon(icons::x16::Up));
  m_lower_object->setIcon(QIcon(icons::x16::Down));
  m_duplicate_object->setIcon(QIcon(icons::x16::Duplicate));
}

void FlowDocumentActionHandler::connectActions() {
  connect(m_add_group_layer, &QAction::triggered, this,
          &FlowDocumentActionHandler::onAddGroupLayer);
  connect(m_add_node_layer, &QAction::triggered, this,
          &FlowDocumentActionHandler::onAddNodeLayer);
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
  connect(m_remove_object, &QAction::triggered, this,
          &FlowDocumentActionHandler::onRemoveObject);
  connect(m_raise_object, &QAction::triggered, this,
          &FlowDocumentActionHandler::onRaiseObject);
  connect(m_lower_object, &QAction::triggered, this,
          &FlowDocumentActionHandler::onLowerObject);
  connect(m_duplicate_object, &QAction::triggered, this,
          &FlowDocumentActionHandler::onDuplicateObject);
}

void FlowDocumentActionHandler::updateActions() {
  const auto has_document = m_document != nullptr;
  const auto selected_layers =
      m_document && m_document->getSelectedLayers().size() > 0;
  const auto selected_objects =
      m_document && m_document->getSelectedObject().size() > 0;

  m_add_group_layer->setEnabled(has_document);
  m_add_node_layer->setEnabled(has_document);
  m_remove_layer->setEnabled(selected_layers);
  m_raise_layer->setEnabled(selected_layers);
  m_lower_layer->setEnabled(selected_layers);
  m_duplicate_layer->setEnabled(selected_layers);
  m_show_hide_other_layers->setEnabled(selected_layers);
  m_lock_unlock_other_layers->setEnabled(selected_layers);

  m_remove_object->setEnabled(selected_objects);
  m_raise_object->setEnabled(selected_objects);
  m_lower_object->setEnabled(selected_objects);
  m_duplicate_object->setEnabled(selected_objects);
}

void FlowDocumentActionHandler::retranslateUi() {
  m_add_group_layer->setText(tr("&Group Layer"));
  m_add_group_layer->setWhatsThis(tr("Create Group Layer"));

  m_add_node_layer->setText(tr("&Node Layer"));
  m_add_node_layer->setWhatsThis(tr("Create Node Layer"));

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

  m_remove_object->setText(tr("&Remove Objects"));
  m_remove_object->setWhatsThis(tr("Remove Selected Objects"));

  m_raise_object->setText(tr("&Raise Objects"));
  m_raise_object->setWhatsThis(tr("Raise Selected Objects"));

  m_lower_object->setText(tr("&Lower Objects"));
  m_lower_object->setWhatsThis(tr("Lower Selected Objects"));

  m_duplicate_object->setText(tr("&Duplicate Objects"));
  m_duplicate_object->setWhatsThis(tr("Duplicate Selected Objects"));
}

void FlowDocumentActionHandler::registerActions() {
  auto& action_manager = egnite::ActionManager::getInstance();
  action_manager.registerAction(m_add_group_layer, "add_group_layer");
  action_manager.registerAction(m_add_node_layer, "add_node_layer");
  action_manager.registerAction(m_remove_layer, "remove_layer");
  action_manager.registerAction(m_raise_layer, "raise_layer");
  action_manager.registerAction(m_lower_layer, "lower_layer");
  action_manager.registerAction(m_duplicate_layer, "duplicate_layer");
  action_manager.registerAction(m_show_hide_other_layers,
                                "show_hide_other_layers");
  action_manager.registerAction(m_lock_unlock_other_layers,
                                "lock_unlock_other_layers");
  action_manager.registerAction(m_remove_object, "remove_object");
  action_manager.registerAction(m_raise_object, "raise_object");
  action_manager.registerAction(m_lower_object, "lower_object");
  action_manager.registerAction(m_duplicate_object, "duplicate_object");
}

void FlowDocumentActionHandler::unregisterActions() {
  auto& action_manager = egnite::ActionManager::getInstance();
  action_manager.unregisterAction(m_add_group_layer, "add_group_layer");
  action_manager.unregisterAction(m_add_node_layer, "add_node_layer");
  action_manager.unregisterAction(m_remove_layer, "remove_layer");
  action_manager.unregisterAction(m_raise_layer, "raise_layer");
  action_manager.unregisterAction(m_lower_layer, "lower_layer");
  action_manager.unregisterAction(m_duplicate_layer, "duplicate_layer");
  action_manager.unregisterAction(m_show_hide_other_layers,
                                  "show_hide_other_layers");
  action_manager.unregisterAction(m_lock_unlock_other_layers,
                                  "lock_unlock_other_layers");
  action_manager.unregisterAction(m_remove_object, "remove_object");
  action_manager.unregisterAction(m_raise_object, "raise_object");
  action_manager.unregisterAction(m_lower_object, "lower_object");
  action_manager.unregisterAction(m_duplicate_object, "duplicate_object");
}

}  // namespace flow_document