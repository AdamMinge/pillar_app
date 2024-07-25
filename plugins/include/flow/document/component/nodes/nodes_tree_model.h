#ifndef FLOW_DOCUMENT_NODES_TREE_MODEL_H
#define FLOW_DOCUMENT_NODES_TREE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/model/reverse_proxy_model.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowDocument;
class ChangeEvent;
class Layer;
class Node;
class Flow;

/* ------------------------------ NodesTreeModel ---------------------------- */

class LIB_FLOW_DOCUMENT_API NodesTreeModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  enum Column { NameColumn, VisibleColumn };

 public:
  explicit NodesTreeModel(QObject *parent = nullptr);
  ~NodesTreeModel() override;

  void setDocument(FlowDocument *flow_document);
  [[nodiscard]] FlowDocument *getDocument() const;

  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

  [[nodiscard]] QVariant data(const QModelIndex &index,
                              int role) const override;
  [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value,
                             int role);

  [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation,
                                    int role) const override;

  [[nodiscard]] QModelIndex index(Layer *layer, int column = 0) const;
  [[nodiscard]] QModelIndex index(Node *node, int column = 0) const;
  [[nodiscard]] QModelIndex index(int row, int column,
                                  const QModelIndex &parent) const override;

  [[nodiscard]] QModelIndex parent(const QModelIndex &index) const override;

  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
  [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

  [[nodiscard]] Layer *toLayer(const QModelIndex &index) const;
  [[nodiscard]] Node *toNode(const QModelIndex &index) const;

 private:
  void onEvent(const ChangeEvent &event);

  [[nodiscard]] Qt::ItemFlags getFlags(const QModelIndex &index) const;
  [[nodiscard]] QString getName(const QModelIndex &index) const;
  [[nodiscard]] QIcon getIcon(const QModelIndex &index) const;
  [[nodiscard]] Qt::CheckState isVisible(const QModelIndex &index) const;

  void setName(const QModelIndex &index, const QString &name);
  void setVisible(const QModelIndex &index, Qt::CheckState state);

 private:
  FlowDocument *m_document;
  Flow *m_flow;
};

/* ------------------------- OnlyNodesFilterProxyModel ---------------------- */

class OnlyNodesFilterProxyModel : public qtils::QtReverseProxyModel {
 public:
  explicit OnlyNodesFilterProxyModel(QObject *parent = nullptr);
  ~OnlyNodesFilterProxyModel() override;

  bool filterAcceptsRow(int source_row,
                        const QModelIndex &source_parent) const override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_NODES_TREE_MODEL_H
