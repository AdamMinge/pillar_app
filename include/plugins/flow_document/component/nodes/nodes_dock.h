#ifndef FLOW_DOCUMENT_NODES_DOCK_H
#define FLOW_DOCUMENT_NODES_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class NodesDock;
}

namespace flow_document {

class NodesTreeModel;
class FlowDocument;

class FLOW_DOCUMENT_API NodesDock : public QDockWidget {
  Q_OBJECT

 public:
  explicit NodesDock(QWidget *parent = nullptr);
  ~NodesDock() override;

  void setDocument(FlowDocument *document);
  [[nodiscard]] FlowDocument *getDocument() const;

 protected:
  void changeEvent(QEvent *event) override;

 private Q_SLOTS:
  void searchNodes(const QString &search);

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  FlowDocument *m_document;

  QScopedPointer<Ui::NodesDock> m_ui;

  QScopedPointer<NodesTreeModel> m_nodes_model;
  QScopedPointer<QSortFilterProxyModel> m_filter_model;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODES_DOCK_H
