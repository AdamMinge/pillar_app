#ifndef FLOW_DOCUMENT_CONNECTIONS_VIEW_H
#define FLOW_DOCUMENT_CONNECTIONS_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
#include "flow/document/flow/connection.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowDocument;

class LIB_FLOW_DOCUMENT_API ConnectionsView : public QTreeView {
  Q_OBJECT

 public:
  explicit ConnectionsView(QWidget *parent = nullptr);
  ~ConnectionsView() override;

  void setDocument(FlowDocument *document);
  [[nodiscard]] FlowDocument *getDocument() const;

  void setModel(QAbstractItemModel *model) override;

 protected:
  void contextMenuEvent(QContextMenuEvent *event) override;
  void selectionChanged(const QItemSelection &selected,
                        const QItemSelection &deselected) override;
  [[nodiscard]] QItemSelectionModel::SelectionFlags selectionCommand(
      const QModelIndex &index, const QEvent *event = nullptr) const override;

  void mousePressEvent(QMouseEvent *event) override;

 private Q_SLOTS:
  void onCurrentConnectionChanged(Connection *connection);
  void onSelectedConnectionsChanged(const QList<Connection *> &connections);

  void onRowsInserted(const QModelIndex &parent, int first, int last);
  void onRowsRemoved(const QModelIndex &parent, int first, int last);

 private:
  [[nodiscard]] QModelIndex indexAt(const QPoint &position) const;

 private:
  FlowDocument *m_document;
  bool m_updating_selection;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_CONNECTIONS_VIEW_H
