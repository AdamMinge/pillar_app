#ifndef FLOW_DOCUMENT_NODES_VIEW_H
#define FLOW_DOCUMENT_NODES_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/node.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;

class FLOW_DOCUMENT_API NodesView : public QTreeView {
  Q_OBJECT

 public:
  explicit NodesView(QWidget *parent = nullptr);
  ~NodesView() override;

  void setDocument(FlowDocument *document);
  [[nodiscard]] FlowDocument *getDocument() const;

  void setModel(QAbstractItemModel *model) override;

 protected:
  void contextMenuEvent(QContextMenuEvent *event) override;
  void selectionChanged(const QItemSelection &selected,
                        const QItemSelection &deselected) override;
  [[nodiscard]] QItemSelectionModel::SelectionFlags selectionCommand(
      const QModelIndex &index, const QEvent *event = nullptr) const override;

  void mouseMoveEvent(QMouseEvent *event) override;
  [[nodiscard]] bool viewportEvent(QEvent *event) override;

 private Q_SLOTS:
  void onCurrentNodeChanged(Node *node);
  void onCurrentRowChanged(const QModelIndex &index);
  void onSelectedNodesChanged(const QList<Node *> &nodes);

  void onRowsInserted(const QModelIndex &parent, int first, int last);
  void onRowsRemoved(const QModelIndex &parent, int first, int last);

 private:
  FlowDocument *m_document;
  bool m_updating_selection;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODES_VIEW_H
