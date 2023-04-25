#ifndef FLOW_DOCUMENT_FLOW_NODES_TREE_MODEL_H
#define FLOW_DOCUMENT_FLOW_NODES_TREE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_listener.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowNodeFactories;
class FlowNodeFactory;

class FLOW_DOCUMENT_API FlowNodesTreeItem {
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

class FLOW_DOCUMENT_API FlowNodesTreeFactoriesItem : public FlowNodesTreeItem {
 public:
  explicit FlowNodesTreeFactoriesItem(FlowNodeFactories *factories);

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
  [[nodiscard]] Qt::ItemFlags flags() const override;

  [[nodiscard]] FlowNodeFactories *getFlowNodeFactories() const;

 private:
  FlowNodeFactories *m_factories;
};

class FLOW_DOCUMENT_API FlowNodesTreeFactoryItem : public FlowNodesTreeItem {
 public:
  explicit FlowNodesTreeFactoryItem(FlowNodeFactory *factory);

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
  [[nodiscard]] Qt::ItemFlags flags() const override;

  [[nodiscard]] FlowNodeFactory *getFlowNodeFactory() const;

 private:
  FlowNodeFactory *m_factory;
};

class FLOW_DOCUMENT_API FlowNodesTreeModel
    : public QAbstractItemModel,
      public egnite::PluginListener<FlowNodeFactories> {
  Q_OBJECT

 public:
  enum Role {
    NameRole = Qt::UserRole + 1,
    IconRole,
  };

  enum Column { NameColumn };

 public:
  explicit FlowNodesTreeModel(QObject *parent = nullptr);
  ~FlowNodesTreeModel() override;

  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

  [[nodiscard]] QVariant data(const QModelIndex &index,
                              int role) const override;
  [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation,
                                    int role) const override;

  [[nodiscard]] QModelIndex index(int row, int column,
                                  const QModelIndex &parent) const override;
  [[nodiscard]] QModelIndex parent(const QModelIndex &index) const override;

  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
  [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

  [[nodiscard]] QMimeData *mimeData(
      const QModelIndexList &indexes) const override;
  [[nodiscard]] QStringList mimeTypes() const override;

 protected:
  void addedObject(FlowNodeFactories *factories) override;
  void removedObject(FlowNodeFactories *factories) override;

 private:
  [[nodiscard]] QByteArray createMimeData(const QModelIndexList &indexes) const;

 private:
  QList<FlowNodesTreeFactoriesItem *> m_root_items;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_NODES_TREE_MODEL_H
