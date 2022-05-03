#ifndef PLUGIN_FLOW_FLOW_NODES_TREE_MODEL_H
#define PLUGIN_FLOW_FLOW_NODES_TREE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
/* ----------------------------------- Local -------------------------------- */
#include <flow/libflow/plugin_listener.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{
  class NodeFactories;
  class NodeFactory;
}// namespace flow::node

class FLOW_DOCUMENT_API FlowNodesTreeItem
{
public:
  explicit FlowNodesTreeItem();
  ~FlowNodesTreeItem();

  [[nodiscard]] FlowNodesTreeItem *getParent() const;

  void addChild(FlowNodesTreeItem *child);
  void removeChild(FlowNodesTreeItem *child);

  [[nodiscard]] const FlowNodesTreeItem *getChild(int row) const;
  [[nodiscard]] FlowNodesTreeItem *getChild(int row);
  [[nodiscard]] int getChildCount() const;
  [[nodiscard]] int findChild(FlowNodesTreeItem *child) const;

  [[nodiscard]] virtual QString getName() const = 0;
  [[nodiscard]] virtual QIcon getIcon() const = 0;

  [[nodiscard]] virtual Qt::ItemFlags flags() const = 0;

private:
  FlowNodesTreeItem *m_parent;
  QList<FlowNodesTreeItem *> m_children;
};

class FLOW_DOCUMENT_API FlowNodesTreeFactoriesItem : public FlowNodesTreeItem
{
public:
  explicit FlowNodesTreeFactoriesItem(flow::node::NodeFactories *factories);

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
  [[nodiscard]] Qt::ItemFlags flags() const override;

  [[nodiscard]] flow::node::NodeFactories *getNodeFactories() const;

private:
  flow::node::NodeFactories *m_factories;
};

class FLOW_DOCUMENT_API FlowNodesTreeFactoryItem : public FlowNodesTreeItem
{
public:
  explicit FlowNodesTreeFactoryItem(flow::node::NodeFactory *factory);

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
  [[nodiscard]] Qt::ItemFlags flags() const override;

  [[nodiscard]] flow::node::NodeFactory *getNodeFactory() const;

private:
  flow::node::NodeFactory *m_factory;
};

class FLOW_DOCUMENT_API FlowNodesTreeModel
    : public QAbstractItemModel,
      public flow::PluginListener<flow::node::NodeFactories>
{
  Q_OBJECT

public:
  enum Role
  {
    NameRole = Qt::UserRole + 1,
    IconRole,
  };

  enum Column
  {
    NameColumn
  };

public:
  explicit FlowNodesTreeModel(QObject *parent = nullptr);
  ~FlowNodesTreeModel() override;

  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

  [[nodiscard]] QVariant
  data(const QModelIndex &index, int role) const override;
  [[nodiscard]] QVariant
  headerData(int section, Qt::Orientation orientation, int role) const override;

  [[nodiscard]] QModelIndex
  index(int row, int column, const QModelIndex &parent) const override;
  [[nodiscard]] QModelIndex parent(const QModelIndex &index) const override;

  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
  [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

  [[nodiscard]] QMimeData *
  mimeData(const QModelIndexList &indexes) const override;
  [[nodiscard]] QStringList mimeTypes() const override;

protected:
  void addedObject(flow::node::NodeFactories *factories) override;
  void removedObject(flow::node::NodeFactories *factories) override;

private:
  [[nodiscard]] QByteArray createMimeData(const QModelIndexList &indexes) const;

private:
  QList<FlowNodesTreeFactoriesItem *> m_root_items;
};

#endif//PLUGIN_FLOW_FLOW_NODES_TREE_MODEL_H
