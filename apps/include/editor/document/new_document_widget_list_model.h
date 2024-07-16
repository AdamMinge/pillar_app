#ifndef NEW_DOCUMENT_WIDGET_LIST_MODEL_H
#define NEW_DOCUMENT_WIDGET_LIST_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractListModel>
#include <QIcon>
#include <QStringList>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_listener.h>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/stacked_widget/stacked_widget_tree_model.h>
/* -------------------------------------------------------------------------- */

namespace pillar {
class NewDocumentWidgetFactory;
class NewDocumentWidget;
}  // namespace pillar

class NewDocumentWidgetListModel
    : public qtils::QtStackedWidgetTreeModel,
      public pillar::PluginListener<pillar::NewDocumentWidgetFactory> {
  Q_OBJECT

 public:
  explicit NewDocumentWidgetListModel(QObject *parent = nullptr);
  ~NewDocumentWidgetListModel() override;

 protected:
  void addedObject(pillar::NewDocumentWidgetFactory *factory) override;
  void removedObject(pillar::NewDocumentWidgetFactory *factory) override;

 private:
  QMap<pillar::NewDocumentWidgetFactory *, pillar::NewDocumentWidget *>
      m_new_document_widget_by_factory;
};

#endif  // NEW_DOCUMENT_WIDGET_LIST_MODEL_H
