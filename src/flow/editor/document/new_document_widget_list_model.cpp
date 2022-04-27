/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/new_document_widget_list_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/document/new_document_widget.h>
#include <flow/libflow/document/new_document_widget_factory.h>
/* -------------------------------------------------------------------------- */

NewDocumentWidgetListModel::NewDocumentWidgetListModel(QObject *parent)
    : QtStackedWidgetTreeModel(parent)
{
  loadObjects();
}

NewDocumentWidgetListModel::~NewDocumentWidgetListModel() = default;

void NewDocumentWidgetListModel::addedObject(
  flow::document::NewDocumentWidgetFactory *factory)
{
  auto settings_widget = factory->create().release();
  m_new_document_widget_by_factory[factory] = settings_widget;

  append(
    new utils::QtStackedWidgetTreeItem(settings_widget, factory->getIcon()),
    QModelIndex{});
}

void NewDocumentWidgetListModel::removedObject(
  flow::document::NewDocumentWidgetFactory *factory)
{
  if (m_new_document_widget_by_factory.contains(factory))
  {
    auto index = getIndexBy(
      Role::WidgetRole,
      QVariant::fromValue(m_new_document_widget_by_factory[factory]),
      QModelIndex{});
    remove(index);
  }
}
