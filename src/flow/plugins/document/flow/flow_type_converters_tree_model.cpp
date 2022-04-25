/* ------------------------------------ Qt ---------------------------------- */
#include <QMimeData>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter_factory.h>
#include <flow/libflow/plugin_manager.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_type_converters_tree_model.h"
/* -------------------------------------------------------------------------- */

/* ------------------------ FlowTypeConvertersTreeItem ---------------------- */

FlowTypeConvertersTreeItem::FlowTypeConvertersTreeItem() : m_parent(nullptr) {}

FlowTypeConvertersTreeItem::~FlowTypeConvertersTreeItem()
{
  qDeleteAll(m_children);
}

FlowTypeConvertersTreeItem *FlowTypeConvertersTreeItem::getParent() const
{
  return m_parent;
}

void FlowTypeConvertersTreeItem::addChild(FlowTypeConvertersTreeItem *child)
{
  if (!m_children.contains(child))
  {
    if (child->m_parent) child->m_parent->removeChild(child);

    m_children.append(child);
    child->m_parent = this;
  }
}

void FlowTypeConvertersTreeItem::removeChild(FlowTypeConvertersTreeItem *child)
{
  if (m_children.contains(child))
  {
    m_children.removeOne(child);
    child->m_parent = nullptr;
  }
}

const FlowTypeConvertersTreeItem *
FlowTypeConvertersTreeItem::getChild(int row) const
{
  if (row < 0 || row >= m_children.size()) return nullptr;
  return m_children.at(row);
}

FlowTypeConvertersTreeItem *FlowTypeConvertersTreeItem::getChild(int row)
{
  if (row < 0 || row >= m_children.size()) return nullptr;
  return m_children.at(row);
}

int FlowTypeConvertersTreeItem::getChildCount() const
{
  return static_cast<int>(m_children.count());
}

int FlowTypeConvertersTreeItem::findChild(
  FlowTypeConvertersTreeItem *child) const
{
  return static_cast<int>(m_children.indexOf(child));
}

/* ------------------- FlowTypeConvertersTreeFactoriesItem ------------------ */

FlowTypeConvertersTreeFactoriesItem::FlowTypeConvertersTreeFactoriesItem(
  flow::node::TypeConverterFactories *factories)
    : m_factories(factories)
{
  for (const auto &type_converter_id : factories->getTypeConverterIds())
    addChild(new FlowTypeConvertersTreeFactoryItem(
      factories->getFactory(type_converter_id)));
}

QString FlowTypeConvertersTreeFactoriesItem::getName() const
{
  return m_factories->getName();
}

QIcon FlowTypeConvertersTreeFactoriesItem::getIcon() const
{
  return m_factories->getIcon();
}

Qt::ItemFlags FlowTypeConvertersTreeFactoriesItem::flags() const
{
  return Qt::NoItemFlags;
}

flow::node::TypeConverterFactories *
FlowTypeConvertersTreeFactoriesItem::getTypeConverterFactories() const
{
  return m_factories;
}

/* --------------------- FlowTypeConvertersTreeFactoryItem ------------------ */

FlowTypeConvertersTreeFactoryItem::FlowTypeConvertersTreeFactoryItem(
  flow::node::TypeConverterFactory *factory)
    : m_factory(factory)
{}

QString FlowTypeConvertersTreeFactoryItem::getName() const
{
  return m_factory->getName();
}

QIcon FlowTypeConvertersTreeFactoryItem::getIcon() const
{
  return m_factory->getIcon();
}

Qt::ItemFlags FlowTypeConvertersTreeFactoryItem::flags() const
{
  return Qt::ItemIsDragEnabled;
}

flow::node::TypeConverterFactory *
FlowTypeConvertersTreeFactoryItem::getTypeConverterFactory() const
{
  return m_factory;
}

/* ---------------------------- FlowConvertersTreeModel -------------------------- */

FlowConvertersTreeModel::FlowConvertersTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
  loadObjects();
}

FlowConvertersTreeModel::~FlowConvertersTreeModel()
{
  qDeleteAll(m_root_items);
}

Qt::ItemFlags FlowConvertersTreeModel::flags(const QModelIndex &index) const
{
  auto item =
    static_cast<FlowTypeConvertersTreeItem *>(index.internalPointer());
  return QAbstractItemModel::flags(index) | item->flags();
}

QVariant FlowConvertersTreeModel::data(const QModelIndex &index, int role) const
{
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return QVariant{};

  auto item =
    static_cast<FlowTypeConvertersTreeItem *>(index.internalPointer());
  switch (role)
  {
    case Qt::DisplayRole:
    case Role::NameRole:
      return item->getName();

    case Qt::DecorationRole:
    case Role::IconRole:
      return item->getIcon();

    default:
      return QVariant{};
  }
}

QVariant FlowConvertersTreeModel::headerData(
  int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
    return QVariant{};

  switch (section)// NOLINT(hicpp-multiway-paths-covered)
  {
    case Column::NameColumn:
      return tr("Name");
    default:
      return QVariant{};
  }
}

QModelIndex FlowConvertersTreeModel::index(
  int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent)) return QModelIndex{};

  FlowTypeConvertersTreeItem *parent_item{nullptr};
  if (parent.isValid())
  {
    parent_item =
      static_cast<FlowTypeConvertersTreeItem *>(parent.internalPointer());
    return createIndex(row, column, parent_item->getChild(row));
  } else
  {
    return createIndex(row, column, m_root_items.at(row));
  }
}

QModelIndex FlowConvertersTreeModel::parent(const QModelIndex &index) const
{
  if (!index.isValid()) return QModelIndex{};

  auto child_item =
    static_cast<FlowTypeConvertersTreeItem *>(index.internalPointer());
  auto item = child_item->getParent();

  if (m_root_items.contains(item))
  {
    auto row = static_cast<int>(m_root_items.indexOf(item));
    return createIndex(row, 0, item);
  } else
  {
    auto parent_item = item ? item->getParent() : nullptr;
    if (!parent_item) return QModelIndex{};

    auto row = parent_item->findChild(item);
    return createIndex(row, 0, item);
  }
}

int FlowConvertersTreeModel::rowCount(const QModelIndex &parent) const
{
  if (parent.column() > 0) return 0;

  if (!parent.isValid()) return static_cast<int>(m_root_items.size());
  else
    return static_cast<FlowTypeConvertersTreeItem *>(parent.internalPointer())
      ->getChildCount();
}

int FlowConvertersTreeModel::columnCount(const QModelIndex &parent) const
{
  return 1;
}

QMimeData *
FlowConvertersTreeModel::mimeData(const QModelIndexList &indexes) const
{
  auto mime_data = new QMimeData;
  mime_data->setData(
    QLatin1String("flow/type_converter"), createMimeData(indexes));

  return mime_data;
}

QStringList FlowConvertersTreeModel::mimeTypes() const
{
  return QStringList{} << QLatin1String("flow/type_converter");
}

void FlowConvertersTreeModel::addedObject(
  flow::node::TypeConverterFactories *factories)
{
  auto factories_item =
    std::make_unique<FlowTypeConvertersTreeFactoriesItem>(factories);
  auto index_to_insert = static_cast<int>(m_root_items.count());

  beginInsertRows(QModelIndex{}, index_to_insert, index_to_insert);
  m_root_items.insert(index_to_insert, factories_item.release());
  endInsertRows();
}

void FlowConvertersTreeModel::removedObject(
  flow::node::TypeConverterFactories *factories)
{
  auto found_root = std::find_if(
    m_root_items.begin(), m_root_items.end(), [factories](auto item) {
      return item->getTypeConverterFactories() == factories;
    });

  if (found_root != m_root_items.end())
  {
    auto index_to_remove =
      static_cast<int>(std::distance(m_root_items.begin(), found_root));

    beginRemoveRows(QModelIndex{}, index_to_remove, index_to_remove);
    m_root_items.remove(index_to_remove);
    endRemoveRows();
  }
}

QByteArray
FlowConvertersTreeModel::createMimeData(const QModelIndexList &indexes) const
{
  return QByteArray{};
}

/*
void FlowConvertersTreeModel::enabledPlugin(QObject *object)
{
  if (
    auto factory_container =
      qobject_cast<node::ConverterFactoryContainer *>(object))
  {
    auto factory_container_item =
      std::make_unique<FlowConvertersTreeNodeFactoryContainerItem>(
        factory_container);

    for (auto &factory : *factory_container)
    {
      factory_container_item->addChild(
        new FlowConvertersTreeNodeFactoryItem(factory.get()));
    }

    auto index_to_insert = static_cast<int>(m_root_items.count());

    beginInsertRows(QModelIndex{}, index_to_insert, index_to_insert);
    m_root_items.insert(index_to_insert, factory_container_item.release());
    endInsertRows();
  }
}

void FlowConvertersTreeModel::disabledPlugin(QObject *object)
{
  if (
    auto factory_container =
      qobject_cast<node::ConverterFactoryContainer *>(object))
  {
    auto found_root = std::find_if(
      m_root_items.begin(), m_root_items.end(), [factory_container](auto item) {
        return item->getConverterFactoryContainer() == factory_container;
      });

    if (found_root != m_root_items.end())
    {
      auto index_to_remove =
        static_cast<int>(std::distance(m_root_items.begin(), found_root));

      beginRemoveRows(QModelIndex{}, index_to_remove, index_to_remove);
      m_root_items.remove(index_to_remove);
      endRemoveRows();
    }
  }
}
*/
