#ifndef NEW_DOCUMENT_WIDGET_LIST_MODEL_H
#define NEW_DOCUMENT_WIDGET_LIST_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractListModel>
#include <QIcon>
#include <QStringList>
/* ----------------------------------- Flow --------------------------------- */
#include <flow/plugin_listener.h>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/stacked_widget/stacked_widget_tree_model.h>
/* -------------------------------------------------------------------------- */

namespace flow {
class NewDocumentWidgetFactory;
class NewDocumentWidget;
}  // namespace flow

class NewDocumentWidgetListModel
    : public utils::QtStackedWidgetTreeModel,
      public flow::PluginListener<flow::NewDocumentWidgetFactory> {
  Q_OBJECT

 public:
  explicit NewDocumentWidgetListModel(QObject *parent = nullptr);
  ~NewDocumentWidgetListModel() override;

 protected:
  void addedObject(flow::NewDocumentWidgetFactory *factory) override;
  void removedObject(flow::NewDocumentWidgetFactory *factory) override;

 private:
  std::map<flow::NewDocumentWidgetFactory *, flow::NewDocumentWidget *>
      m_new_document_widget_by_factory;
};

#endif  // NEW_DOCUMENT_WIDGET_LIST_MODEL_H
