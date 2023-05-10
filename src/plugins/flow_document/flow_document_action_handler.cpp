/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_action_handler.h"

#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

QScopedPointer<FlowDocumentActionHandler>
    FlowDocumentActionHandler::m_instance =
        QScopedPointer<FlowDocumentActionHandler>(nullptr);

FlowDocumentActionHandler& FlowDocumentActionHandler::getInstance() {
  if (m_instance.isNull()) m_instance.reset(new FlowDocumentActionHandler);

  return *m_instance;
}

void FlowDocumentActionHandler::deleteInstance() { m_instance.reset(nullptr); }

FlowDocumentActionHandler::FlowDocumentActionHandler() {
  m_add_group_layer = new QAction(this);
  m_add_group_layer->setIcon(
      QIcon(":/plugins/flow_document/images/16x16/add.png"));

  m_add_node_layer = new QAction(this);
  m_add_node_layer->setIcon(
      QIcon(":/plugins/flow_document/images/16x16/add.png"));

  m_remove_layer = new QAction(this);
  m_remove_layer->setIcon(
      QIcon(":/plugins/flow_document/images/16x16/remove.png"));

  m_raise_layer = new QAction(this);
  m_raise_layer->setIcon(QIcon(":/plugins/flow_document/images/16x16/up.png"));

  m_lower_layer = new QAction(this);
  m_lower_layer->setIcon(
      QIcon(":/plugins/flow_document/images/16x16/down.png"));

  m_duplicate_layer = new QAction(this);
  m_duplicate_layer->setIcon(
      QIcon(":/plugins/flow_document/images/16x16/duplicate.png"));

  m_show_hide_other_layers = new QAction(this);
  m_show_hide_other_layers->setIcon(
      QIcon(":/plugins/flow_document/images/16x16/show_hide_others.png"));

  m_lock_unlock_other_layers = new QAction(this);
  m_lock_unlock_other_layers->setIcon(
      QIcon(":/plugins/flow_document/images/16x16/locked.png"));

  m_remove_object = new QAction(this);
  m_remove_object->setIcon(
      QIcon(":/plugins/flow_document/images/16x16/remove.png"));

  m_raise_object = new QAction(this);
  m_raise_object->setIcon(QIcon(":/plugins/flow_document/images/16x16/up.png"));

  m_lower_object = new QAction(this);
  m_lower_object->setIcon(
      QIcon(":/plugins/flow_document/images/16x16/down.png"));

  m_duplicate_object = new QAction(this);
  m_duplicate_object->setIcon(
      QIcon(":/plugins/flow_document/images/16x16/duplicate.png"));

  updateActions();
  retranslateUi();
}

FlowDocumentActionHandler::~FlowDocumentActionHandler() = default;

void FlowDocumentActionHandler::setDocument(FlowDocument* document) {
  if (m_document == document) return;

  m_document = document;
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
  menu->setIcon(QIcon(":/plugins/flow_document/images/16x16/add.png"));

  menu->addAction(m_add_group_layer);
  menu->addAction(m_add_node_layer);

  return menu;
}

void FlowDocumentActionHandler::updateActions() {}

void FlowDocumentActionHandler::retranslateUi() {
  m_add_group_layer->setText(tr("&Group Layer"));
  m_add_node_layer->setText(tr("&Node Layer"));
  m_remove_layer->setText(tr("&Remove Layers"));
  m_raise_layer->setText(tr("&Raise Layers"));
  m_lower_layer->setText(tr("&Lower Layers"));
  m_duplicate_layer->setText(tr("&Duplicate Layers"));
  m_show_hide_other_layers->setText(tr("Show/&Hide Layers"));
  m_lock_unlock_other_layers->setText(tr("Lock/&Unlock Layers"));

  m_remove_object->setText(tr("&Remove Objects"));
  m_raise_object->setText(tr("&Raise Objects"));
  m_lower_object->setText(tr("&Lower Objects"));
  m_duplicate_object->setText(tr("&Duplicate Objects"));
}

}  // namespace flow_document