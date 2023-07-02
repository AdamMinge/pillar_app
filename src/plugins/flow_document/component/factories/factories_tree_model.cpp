/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/factories/factories_tree_model.h"

#include "flow_document/flow/factory/node_factory.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMimeData>
/* -------------------------------------------------------------------------- */

namespace flow_document {

FactoriesTreeModel::FactoriesTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_root(new QStandardItem()) {
  loadObjects();
}

FactoriesTreeModel::~FactoriesTreeModel() = default;

Qt::ItemFlags FactoriesTreeModel::flags(const QModelIndex &index) const {
  return QAbstractItemModel::flags(index) | getFlags(index);
}

QVariant FactoriesTreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  auto item = getItem(index);
  return item ? item->data(role) : QVariant();
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
  if (!hasIndex(row, column, parent)) return QModelIndex();

  auto parent_item = getItem(parent);
  auto child_item = parent_item->child(row, column);
  if (child_item)
    return createIndex(row, column, child_item);
  else
    return QModelIndex();
}

QModelIndex FactoriesTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex();

  auto child_item = getItem(index);
  auto parent_item = child_item->parent();
  if (!parent_item) return QModelIndex();

  if (parent_item == m_root.get()) return QModelIndex();
  return createIndex(parent_item->row(), 0, parent_item);
}

int FactoriesTreeModel::rowCount(const QModelIndex &parent) const {
  auto parent_item = getItem(parent);
  return parent_item->rowCount();
}

int FactoriesTreeModel::columnCount(const QModelIndex &parent) const {
  auto parent_item = getItem(parent);
  return parent_item->columnCount();
}

QMimeData *FactoriesTreeModel::mimeData(const QModelIndexList &indexes) const {
  if (indexes.isEmpty()) return nullptr;

  auto mime_data = new QMimeData;
  QByteArray encoded_data;
  QDataStream stream(&encoded_data, QDataStream::WriteOnly);

  auto factories = QList<ObjectFactory *>{};
  for (const auto &index : indexes) {
    auto factory = toFactory(index);
    if (factories.contains(factory)) continue;
    factories.append(factory);
  }

  for (auto factory : factories) {
    stream << factory->getObjectClassName();
  }

  mime_data->setData(mimetype::Factories, encoded_data);
  return mime_data;
}

QStringList FactoriesTreeModel::mimeTypes() const {
  return QStringList{} << mimetype::Factories;
}

void FactoriesTreeModel::addedObject(ObjectFactory *factory) {
  beginResetModel();

  auto factory_section = getOrCreateFactorySection(factory);
  if (factory_section) {
    Q_ASSERT(!findFactory(factory_section, factory));
    factory_section->appendRow(createFactory(factory));
  }

  endResetModel();
}

void FactoriesTreeModel::removedObject(ObjectFactory *factory) {
  beginResetModel();

  auto factory_section = getOrCreateFactorySection(factory);
  if (factory_section) {
    auto factory_item = findFactory(factory_section, factory);
    Q_ASSERT(factory_item);

    factory_section->removeRow(factory_item->row());
    if (factory_section->rowCount() == 0) {
      auto type_section = getOrCreateTypeSection(factory);
      type_section->removeRow(factory_section->row());
    }
  }

  endResetModel();
}

QStandardItem *FactoriesTreeModel::getOrCreateFactorySection(
    ObjectFactory *factory) {
  auto type_section = getOrCreateTypeSection(factory);
  const auto section_name = factory->getSection();
  for (auto row = 0; row < type_section->rowCount(); ++row) {
    auto child_item = type_section->child(row);
    if (child_item->text() == section_name) {
      return child_item;
    }
  }

  auto section_item = createSection(section_name);
  type_section->appendRow(section_item);

  return section_item;
}

QStandardItem *FactoriesTreeModel::createFactory(ObjectFactory *factory) {
  auto item = new QStandardItem(factory->getName());
  item->setData(QVariant::fromValue(factory), Qt::UserRole);
  item->setData(factory->getIcon(), Qt::DecorationRole);
  item->setData(factory->getName(), Qt::DisplayRole);

  return item;
}

QStandardItem *FactoriesTreeModel::createSection(const QString &name) {
  auto item = new QStandardItem(name);
  item->setData(QIcon(icons::x32::Group), Qt::DecorationRole);

  return item;
}

QStandardItem *FactoriesTreeModel::getOrCreateTypeSection(
    ObjectFactory *factory) {
  for (auto row = 0; row < m_root->rowCount(); ++row) {
    auto child = m_root->child(row);
    if (child->text() == factory->getType()) return child;
  }

  auto type_section = createSection(factory->getType());
  m_root->appendRow(type_section);

  return type_section;
}

QStandardItem *FactoriesTreeModel::findFactory(QStandardItem *section,
                                               ObjectFactory *factory) const {
  Q_ASSERT(section);
  for (auto row = 0; row < section->rowCount(); ++row) {
    auto child_item = section->child(row);
    auto child_item_factory =
        child_item->data(Qt::UserRole).value<ObjectFactory *>();

    if (child_item_factory == factory) return child_item;
  }

  return nullptr;
}

QStandardItem *FactoriesTreeModel::getItem(const QModelIndex &index) const {
  if (index.isValid()) {
    auto item = static_cast<QStandardItem *>(index.internalPointer());
    if (item) return item;
  }

  return m_root.get();
}

Qt::ItemFlags FactoriesTreeModel::getFlags(const QModelIndex &index) const {
  auto item = static_cast<QStandardItem *>(index.internalPointer());
  auto factory = item->data(Qt::UserRole).value<ObjectFactory *>();
  if (!factory) return Qt::NoItemFlags;

  auto flags = Qt::ItemFlags{};
  flags |= Qt::ItemIsDragEnabled;

  return flags;
}

ObjectFactory *FactoriesTreeModel::toFactory(const QModelIndex &index) const {
  auto item = getItem(index);
  if (!item) return nullptr;

  return item->data(Qt::UserRole).value<ObjectFactory *>();
}

}  // namespace flow_document