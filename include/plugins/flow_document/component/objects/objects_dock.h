#ifndef FLOW_DOCUMENT_LAYOUTS_DOCK_H
#define FLOW_DOCUMENT_LAYOUTS_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class ObjectsDock;
}

namespace flow_document {

class ObjectsTreeModel;

class FLOW_DOCUMENT_API ObjectsDock : public QDockWidget {
  Q_OBJECT

 public:
  explicit ObjectsDock(QWidget *parent = nullptr);
  ~ObjectsDock() override;

 protected:
  void changeEvent(QEvent *event) override;

 private Q_SLOTS:
  void searchObjects(const QString &search);

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  QScopedPointer<Ui::ObjectsDock> m_ui;

  QScopedPointer<ObjectsTreeModel> m_objects_model;
  QScopedPointer<QSortFilterProxyModel> m_search_proxy_model;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYOUTS_DOCK_H
