#ifndef FLOW_FLOW_CONVERTERS_TREE_MODEL_H
#define FLOW_FLOW_CONVERTERS_TREE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
/* ------------------------------------ Api --------------------------------- */
#include <flow/modules/api/document/document.h>
/* -------------------------------------------------------------------------- */

namespace node
{
  class ConverterFactory;
  class ConverterFactoryContainer;
}// namespace node

class FlowConvertersTreeItem
{
public:
  explicit FlowConvertersTreeItem();
  ~FlowConvertersTreeItem();

  [[nodiscard]] FlowConvertersTreeItem *getParent() const;

  void addChild(FlowConvertersTreeItem *child);
  void removeChild(FlowConvertersTreeItem *child);

  [[nodiscard]] const FlowConvertersTreeItem *getChild(int row) const;
  [[nodiscard]] FlowConvertersTreeItem *getChild(int row);
  [[nodiscard]] int getChildCount() const;
  [[nodiscard]] int findChild(FlowConvertersTreeItem *child) const;

  [[nodiscard]] virtual QString getName() const = 0;
  [[nodiscard]] virtual QIcon getIcon() const = 0;

private:
  FlowConvertersTreeItem *m_parent;
  QList<FlowConvertersTreeItem *> m_children;
};

class FlowConvertersTreeNodeFactoryContainerItem : public FlowConvertersTreeItem
{
public:
  explicit FlowConvertersTreeNodeFactoryContainerItem(
    node::ConverterFactoryContainer *factory_container);

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
  [[nodiscard]] node::ConverterFactoryContainer *
  getConverterFactoryContainer() const;

private:
  node::ConverterFactoryContainer *m_factory_container;
};

class FlowConvertersTreeNodeFactoryItem : public FlowConvertersTreeItem
{
public:
  explicit FlowConvertersTreeNodeFactoryItem(node::ConverterFactory *factory);

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
  [[nodiscard]] node::ConverterFactory *getConverterFactory() const;

private:
  node::ConverterFactory *m_factory;
};

class FlowConvertersTreeModel : public QAbstractItemModel
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
  explicit FlowConvertersTreeModel(QObject *parent = nullptr);
  ~FlowConvertersTreeModel() override;

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
  QList<FlowConvertersTreeNodeFactoryContainerItem *> m_root_items;
};

#endif//FLOW_FLOW_CONVERTERS_TREE_MODEL_H
