#ifndef FLOW_DOCUMENT_FACTORIES_DOCK_H
#define FLOW_DOCUMENT_FACTORIES_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class FactoriesDock;
}

namespace flow_document {

class FactoriesTreeModel;
class FactoriesTreeDelegate;

class FLOW_DOCUMENT_API FactoriesDock : public QDockWidget {
  Q_OBJECT

 public:
  explicit FactoriesDock(QWidget *parent = nullptr);
  ~FactoriesDock() override;

 protected:
  void changeEvent(QEvent *event) override;

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  QScopedPointer<Ui::FactoriesDock> m_ui;

  QScopedPointer<FactoriesTreeModel> m_factories_model;
  QScopedPointer<QSortFilterProxyModel> m_factories_filter_model;
  QScopedPointer<FactoriesTreeDelegate> m_factories_delegate;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FACTORIES_DOCK_H
