#ifndef FLOW_DOCUMENT_FACTORIES_TREE_MODEL_H
#define FLOW_DOCUMENT_FACTORIES_TREE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_listener.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class GroupFactory;
class Factory;

class FLOW_DOCUMENT_API FactoriesTreeModel
    : public QAbstractItemModel,
      public egnite::PluginListener<GroupFactory> {
  Q_OBJECT

 public:
  enum Role {
    NameRole = Qt::UserRole + 1,
    IconRole,
  };

  enum Column { NameColumn };

 public:
  explicit FactoriesTreeModel(QObject *parent = nullptr);
  ~FactoriesTreeModel() override;

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
  void addedObject(GroupFactory *group_factories) override;
  void removedObject(GroupFactory *group_factories) override;

 private:
  [[nodiscard]] QString getName(Factory *factory) const;
  [[nodiscard]] QIcon getIcon(Factory *factory) const;
  [[nodiscard]] Qt::ItemFlags getFlags(Factory *factory) const;

 private:
  QList<GroupFactory *> m_group_factories;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FACTORIES_TREE_MODEL_H
