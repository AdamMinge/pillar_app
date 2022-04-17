#ifndef FLOW_FLOW_NODES_TREE_MODEL_H
#define FLOW_FLOW_NODES_TREE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
/* ------------------------------------ Api --------------------------------- */
#include <flow/modules/api/document/document.h>
/* -------------------------------------------------------------------------- */

namespace node
{
  class NodeFactoryContainer;
  class NodeFactory;
}// namespace node

class FlowNodesTreeItem
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

private:
  FlowNodesTreeItem *m_parent;
  QList<FlowNodesTreeItem *> m_children;
};

class FlowNodesTreeNodeFactoryContainerItem : public FlowNodesTreeItem
{
public:
  explicit FlowNodesTreeNodeFactoryContainerItem(
    node::NodeFactoryContainer *factory_container);

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
  [[nodiscard]] node::NodeFactoryContainer *getNodeFactoryContainer() const;

private:
  node::NodeFactoryContainer *m_factory_container;
};

class FlowNodesTreeNodeFactoryItem : public FlowNodesTreeItem
{
public:
  explicit FlowNodesTreeNodeFactoryItem(node::NodeFactory *factory);

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
  [[nodiscard]] node::NodeFactory *getNodeFactory() const;

private:
  node::NodeFactory *m_factory;
};

class FlowNodesTreeModel : public QAbstractItemModel
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

private Q_SLOTS:
  void init();
  void enabledPlugin(QObject *object);
  void disabledPlugin(QObject *object);

private:
  QList<FlowNodesTreeNodeFactoryContainerItem *> m_root_items;
};

#endif//FLOW_FLOW_NODES_TREE_MODEL_H
