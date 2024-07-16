#ifndef FLOW_DOCUMENT_FACTORIES_TREE_MODEL_H
#define FLOW_DOCUMENT_FACTORIES_TREE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
#include <QStandardItem>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_listener.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class ObjectFactory;

class FLOW_DOCUMENT_API FactoriesTreeModel
    : public QAbstractItemModel,
      public pillar::PluginListener<ObjectFactory> {
  Q_OBJECT

 public:
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
  void addedObject(ObjectFactory *factory) override;
  void removedObject(ObjectFactory *factory) override;

 private:
  [[nodiscard]] QStandardItem *getOrCreateFactorySection(
      ObjectFactory *factory);
  [[nodiscard]] QStandardItem *createFactory(ObjectFactory *factory);
  [[nodiscard]] QStandardItem *createSection(const QString &name);

  [[nodiscard]] QStandardItem *getOrCreateTypeSection(ObjectFactory *factory);
  [[nodiscard]] QStandardItem *findFactory(QStandardItem *section,
                                           ObjectFactory *factory) const;

  [[nodiscard]] QStandardItem *getItem(const QModelIndex &index) const;
  [[nodiscard]] Qt::ItemFlags getFlags(const QModelIndex &index) const;

  [[nodiscard]] ObjectFactory *toFactory(const QModelIndex &index) const;

 private:
  QScopedPointer<QStandardItem> m_root;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FACTORIES_TREE_MODEL_H
