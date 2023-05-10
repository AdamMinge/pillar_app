/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/factories/factories_tree_model.h"

#include "flow_document/flow/group_factory.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMimeData>
/* -------------------------------------------------------------------------- */

namespace flow_document {

FactoriesTreeModel::FactoriesTreeModel(QObject *parent)
    : QAbstractItemModel(parent) {
  loadObjects();
}

FactoriesTreeModel::~FactoriesTreeModel() = default;

Qt::ItemFlags FactoriesTreeModel::flags(const QModelIndex &index) const {
  auto item = static_cast<Factory *>(index.internalPointer());
  return QAbstractItemModel::flags(index) | getFlags(item);
}

QVariant FactoriesTreeModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return QVariant{};

  auto item = static_cast<Factory *>(index.internalPointer());
  switch (role) {
    case Qt::DisplayRole:
    case Role::NameRole:
      return getName(item);

    case Qt::DecorationRole:
    case Role::IconRole:
      return getIcon(item);

    default:
      return QVariant{};
  }
}

QVariant FactoriesTreeModel::headerData(int section,
                                        Qt::Orientation orientation,
                                        int role) const {
  if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
    return QVariant{};

  switch (section) {
    case Column::NameColumn:
      return tr("Name");
    default:
      return QVariant{};
  }
}

QModelIndex FactoriesTreeModel::index(int row, int column,
                                      const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex{};

  GroupFactory *parent_item{nullptr};
  if (parent.isValid()) {
    parent_item = static_cast<GroupFactory *>(parent.internalPointer());
    return createIndex(row, column, parent_item->at(row));
  } else {
    return createIndex(row, column, m_group_factories.at(row));
  }
}

QModelIndex FactoriesTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex{};

  auto child_item = static_cast<Factory *>(index.internalPointer());
  auto item = child_item->getParent();

  if (m_group_factories.contains(item)) {
    auto row = static_cast<int>(m_group_factories.indexOf(item));
    return createIndex(row, 0, item);
  } else {
    auto parent_item = item ? item->getParent() : nullptr;
    if (!parent_item) return QModelIndex{};

    auto row = parent_item->indexOf(item);
    return createIndex(row, 0, item);
  }
}

int FactoriesTreeModel::rowCount(const QModelIndex &parent) const {
  if (parent.column() > 0) return 0;

  if (!parent.isValid())
    return static_cast<int>(m_group_factories.size());
  else {
    auto factory = static_cast<Factory *>(parent.internalPointer());
    if (factory->getType() == Factory::Type::GroupFactory) {
      auto group_factory = static_cast<GroupFactory *>(factory);
      return group_factory->size();
    }

    return 0;
  }
}

int FactoriesTreeModel::columnCount(const QModelIndex &parent) const {
  return 1;
}

QMimeData *FactoriesTreeModel::mimeData(const QModelIndexList &indexes) const {
  // TODO
  auto mime_data = new QMimeData;
  return mime_data;
}

QStringList FactoriesTreeModel::mimeTypes() const {
  // TODO
  return QStringList{};
}

void FactoriesTreeModel::addedObject(GroupFactory *group_factories) {
  auto index_to_insert = static_cast<int>(m_group_factories.count());

  beginInsertRows(QModelIndex{}, index_to_insert, index_to_insert);
  m_group_factories.insert(index_to_insert, group_factories);
  endInsertRows();
}

void FactoriesTreeModel::removedObject(GroupFactory *group_factories) {
  auto index_to_remove = m_group_factories.indexOf(group_factories);

  beginRemoveRows(QModelIndex{}, index_to_remove, index_to_remove);
  m_group_factories.remove(index_to_remove);
  endRemoveRows();
}

QString FactoriesTreeModel::getName(Factory *factory) const {
  return factory->getName();
}

QIcon FactoriesTreeModel::getIcon(Factory *factory) const {
  switch (factory->getType()) {
    case Factory::Type::GroupFactory:
      return QIcon(":/plugins/flow_document/images/32x32/dir.png");

    case Factory::Type::NodeFactory:
      return QIcon(":/plugins/flow_document/images/32x32/node.png");
  }

  return QIcon{};
}

Qt::ItemFlags FactoriesTreeModel::getFlags(Factory *factory) const {
  auto flags = Qt::ItemFlags{Qt::NoItemFlags};
  switch (factory->getType()) {
    case Factory::Type::NodeFactory:
      flags |= Qt::ItemIsDragEnabled;
      break;
  }

  return flags;
}

}  // namespace flow_document