/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/factories/factories_tree_model.h"

#include "flow_document/flow/factory/factory.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMimeData>
/* -------------------------------------------------------------------------- */

namespace flow_document {

FactoriesTreeModel::FactoriesTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_root(new QStandardItem()) {
  m_root->insertRow(Section::Nodes, createSection(tr("Nodes")));

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
  // TODO
  auto mime_data = new QMimeData;
  return mime_data;
}

QStringList FactoriesTreeModel::mimeTypes() const {
  // TODO
  return QStringList{};
}

void FactoriesTreeModel::addedObject(Factory *factory) {
  beginResetModel();

  auto factory_section = getOrCreateFactorySection(factory);
  if (factory_section) {
    Q_ASSERT(!findFactory(factory_section, factory));
    factory_section->appendRow(createFactory(factory));
  }

  endResetModel();
}

void FactoriesTreeModel::removedObject(Factory *factory) {
  beginResetModel();

  auto factory_section = getOrCreateFactorySection(factory);
  if (factory_section) {
    auto factory_item = findFactory(factory_section, factory);
    Q_ASSERT(factory_item);

    factory_section->removeRow(factory_item->row());
    if (factory_section->rowCount() == 0) {
      auto type_section = findTypeSection(factory);
      type_section->removeRow(factory_section->row());
    }
  }

  endResetModel();
}

QStandardItem *FactoriesTreeModel::getOrCreateFactorySection(Factory *factory) {
  auto type_section = findTypeSection(factory);
  if (!type_section) return nullptr;

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

QStandardItem *FactoriesTreeModel::createFactory(Factory *factory) {
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

QStandardItem *FactoriesTreeModel::findTypeSection(Factory *factory) const {
  switch (factory->getType()) {
    case Factory::Type::NodeFactory:
      return m_root->child(Section::Nodes);
  }

  return nullptr;
}

QStandardItem *FactoriesTreeModel::findFactory(QStandardItem *section,
                                               Factory *factory) const {
  Q_ASSERT(section);
  for (auto row = 0; row < section->rowCount(); ++row) {
    auto child_item = section->child(row);
    auto child_item_factory = child_item->data(Qt::UserRole).value<Factory *>();

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
  auto factory = item->data(Qt::UserRole).value<Factory *>();
  if (!factory) return Qt::NoItemFlags;

  auto flags = Qt::ItemFlags{};
  switch (factory->getType()) {
    case Factory::Type::NodeFactory:
      flags |= Qt::ItemIsDragEnabled;
      break;
  }

  return flags;
}

}  // namespace flow_document