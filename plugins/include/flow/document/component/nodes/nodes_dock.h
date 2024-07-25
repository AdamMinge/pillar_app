#ifndef FLOW_DOCUMENT_NODES_DOCK_H
#define FLOW_DOCUMENT_NODES_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/dock_widget.h"
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class NodesDock;
}

namespace flow {

class NodesTreeModel;
class FlowDocument;

class LIB_FLOW_DOCUMENT_API NodesDock : public FlowDockWidget {
  Q_OBJECT

 public:
  explicit NodesDock(QWidget *parent = nullptr);
  ~NodesDock() override;

 protected Q_SLOTS:
  void changeEvent(QEvent *event) override;
  void onDocumentChanged(FlowDocument *from, FlowDocument *to) override;

 private Q_SLOTS:
  void searchNodes(const QString &search);

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  QScopedPointer<Ui::NodesDock> m_ui;

  QScopedPointer<NodesTreeModel> m_nodes_model;
  QScopedPointer<QSortFilterProxyModel> m_filter_model;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_NODES_DOCK_H
