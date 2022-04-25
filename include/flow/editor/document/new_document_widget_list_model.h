#ifndef FLOW_NEW_DOCUMENT_WIDGET_LIST_MODEL_H
#define FLOW_NEW_DOCUMENT_WIDGET_LIST_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractListModel>
#include <QIcon>
#include <QStringList>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/plugin_listener.h>
/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/stacked_widget/stacked_widget_tree_model.h>
/* -------------------------------------------------------------------------- */

namespace flow::document
{
  class NewDocumentWidgetFactory;
  class NewDocumentWidget;
}// namespace flow::document

class NewDocumentWidgetListModel
    : public utils::QtStackedWidgetTreeModel,
      public flow::PluginListener<flow::document::NewDocumentWidgetFactory>
{
  Q_OBJECT

public:
  explicit NewDocumentWidgetListModel(QObject *parent = nullptr);
  ~NewDocumentWidgetListModel() override;

protected:
  void addedObject(flow::document::NewDocumentWidgetFactory *factory) override;
  void
  removedObject(flow::document::NewDocumentWidgetFactory *factory) override;

private:
  std::map<
    flow::document::NewDocumentWidgetFactory *,
    flow::document::NewDocumentWidget *>
    m_new_document_widget_by_factory;
};

#endif//FLOW_NEW_DOCUMENT_WIDGET_LIST_MODEL_H
