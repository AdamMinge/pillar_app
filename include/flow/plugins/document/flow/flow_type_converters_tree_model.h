#ifndef FLOW_FLOW_TYPE_CONVERTERS_TREE_MODEL_H
#define FLOW_FLOW_TYPE_CONVERTERS_TREE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/plugin_listener.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{
  class TypeConverterFactory;
  class TypeConverterFactories;
}// namespace flow::node

class FLOW_DOCUMENT_API FlowTypeConvertersTreeItem
{
public:
  explicit FlowTypeConvertersTreeItem();
  ~FlowTypeConvertersTreeItem();

  [[nodiscard]] FlowTypeConvertersTreeItem *getParent() const;

  void addChild(FlowTypeConvertersTreeItem *child);
  void removeChild(FlowTypeConvertersTreeItem *child);

  [[nodiscard]] const FlowTypeConvertersTreeItem *getChild(int row) const;
  [[nodiscard]] FlowTypeConvertersTreeItem *getChild(int row);
  [[nodiscard]] int getChildCount() const;
  [[nodiscard]] int findChild(FlowTypeConvertersTreeItem *child) const;

  [[nodiscard]] virtual QString getName() const = 0;
  [[nodiscard]] virtual QIcon getIcon() const = 0;

  [[nodiscard]] virtual Qt::ItemFlags flags() const = 0;

private:
  FlowTypeConvertersTreeItem *m_parent;
  QList<FlowTypeConvertersTreeItem *> m_children;
};

class FLOW_DOCUMENT_API FlowTypeConvertersTreeFactoriesItem
    : public FlowTypeConvertersTreeItem
{
public:
  explicit FlowTypeConvertersTreeFactoriesItem(
    flow::node::TypeConverterFactories *factories);

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
  [[nodiscard]] Qt::ItemFlags flags() const override;

  [[nodiscard]] flow::node::TypeConverterFactories *
  getTypeConverterFactories() const;

private:
  flow::node::TypeConverterFactories *m_factories;
};

class FLOW_DOCUMENT_API FlowTypeConvertersTreeFactoryItem
    : public FlowTypeConvertersTreeItem
{
public:
  explicit FlowTypeConvertersTreeFactoryItem(
    flow::node::TypeConverterFactory *factory);

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
  [[nodiscard]] Qt::ItemFlags flags() const override;

  [[nodiscard]] flow::node::TypeConverterFactory *
  getTypeConverterFactory() const;

private:
  flow::node::TypeConverterFactory *m_factory;
};

class FLOW_DOCUMENT_API FlowConvertersTreeModel
    : public QAbstractItemModel,
      public flow::PluginListener<flow::node::TypeConverterFactories>
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

  [[nodiscard]] QMimeData *
  mimeData(const QModelIndexList &indexes) const override;
  [[nodiscard]] QStringList mimeTypes() const override;

protected:
  void addedObject(flow::node::TypeConverterFactories *factories) override;
  void removedObject(flow::node::TypeConverterFactories *factories) override;

private:
  [[nodiscard]] QByteArray createMimeData(const QModelIndexList &indexes) const;

private:
  QList<FlowTypeConvertersTreeFactoriesItem *> m_root_items;
};

#endif//FLOW_FLOW_TYPE_CONVERTERS_TREE_MODEL_H
