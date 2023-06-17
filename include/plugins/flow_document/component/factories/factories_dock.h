#ifndef FLOW_DOCUMENT_FACTORIES_DOCK_H
#define FLOW_DOCUMENT_FACTORIES_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/flow_dock_widget.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class FactoriesDock;
}

namespace flow_document {

class FactoriesTreeModel;

class FLOW_DOCUMENT_API FactoriesDock : public FlowDockWidget {
  Q_OBJECT

 public:
  explicit FactoriesDock(QWidget *parent = nullptr);
  ~FactoriesDock() override;

 protected:
  void changeEvent(QEvent *event) override;

 private Q_SLOTS:
  void searchFactories(const QString &search);

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  QScopedPointer<Ui::FactoriesDock> m_ui;

  QScopedPointer<FactoriesTreeModel> m_factories_model;
  QScopedPointer<QSortFilterProxyModel> m_search_proxy_model;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FACTORIES_DOCK_H
