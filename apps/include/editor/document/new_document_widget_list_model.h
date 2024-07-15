#ifndef NEW_DOCUMENT_WIDGET_LIST_MODEL_H
#define NEW_DOCUMENT_WIDGET_LIST_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractListModel>
#include <QIcon>
#include <QStringList>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_listener.h>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/stacked_widget/stacked_widget_tree_model.h>
/* -------------------------------------------------------------------------- */

namespace egnite {
class NewDocumentWidgetFactory;
class NewDocumentWidget;
}  // namespace egnite

class NewDocumentWidgetListModel
    : public qtils::QtStackedWidgetTreeModel,
      public egnite::PluginListener<egnite::NewDocumentWidgetFactory> {
  Q_OBJECT

 public:
  explicit NewDocumentWidgetListModel(QObject *parent = nullptr);
  ~NewDocumentWidgetListModel() override;

 protected:
  void addedObject(egnite::NewDocumentWidgetFactory *factory) override;
  void removedObject(egnite::NewDocumentWidgetFactory *factory) override;

 private:
  QMap<egnite::NewDocumentWidgetFactory *, egnite::NewDocumentWidget *>
      m_new_document_widget_by_factory;
};

#endif  // NEW_DOCUMENT_WIDGET_LIST_MODEL_H
