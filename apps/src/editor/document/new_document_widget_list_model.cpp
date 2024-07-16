/* ----------------------------------- Local -------------------------------- */
#include "document/new_document_widget_list_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/document/new_document_widget.h>
#include <pillar/document/new_document_widget_factory.h>
/* -------------------------------------------------------------------------- */

NewDocumentWidgetListModel::NewDocumentWidgetListModel(QObject *parent)
    : QtStackedWidgetTreeModel(parent) {
  loadObjects();
}

NewDocumentWidgetListModel::~NewDocumentWidgetListModel() {
  qDeleteAll(m_new_document_widget_by_factory);
}

void NewDocumentWidgetListModel::addedObject(
    pillar::NewDocumentWidgetFactory *factory) {
  auto settings_widget = factory->create();
  m_new_document_widget_by_factory[factory] = settings_widget;

  append(
      new qtils::QtStackedWidgetTreeItem(settings_widget, factory->getIcon()),
      QModelIndex{});
}

void NewDocumentWidgetListModel::removedObject(
    pillar::NewDocumentWidgetFactory *factory) {
  if (m_new_document_widget_by_factory.contains(factory)) {
    auto index = getIndexBy(
        Role::WidgetRole,
        QVariant::fromValue(m_new_document_widget_by_factory[factory]),
        QModelIndex{});
    remove(index);
  }
}
