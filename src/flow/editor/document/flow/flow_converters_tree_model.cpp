/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_converters_tree_model.h"
#include "flow/editor/plugin_manager.h"
/* ----------------------------------- Node --------------------------------- */
#include "flow/modules/node/converter_factory.h"
#include "flow/modules/node/converter_factory_container.h"
/* -------------------------------------------------------------------------- */

/* ---------------------------- FlowConvertersTreeItem --------------------------- */

FlowConvertersTreeItem::FlowConvertersTreeItem() : m_parent(nullptr) {}

FlowConvertersTreeItem::~FlowConvertersTreeItem() { qDeleteAll(m_children); }

FlowConvertersTreeItem *FlowConvertersTreeItem::getParent() const
{
  return m_parent;
}

void FlowConvertersTreeItem::addChild(FlowConvertersTreeItem *child)
{
  if (!m_children.contains(child))
  {
    if (child->m_parent) child->m_parent->removeChild(child);

    m_children.append(child);
    child->m_parent = this;
  }
}

void FlowConvertersTreeItem::removeChild(FlowConvertersTreeItem *child)
{
  if (m_children.contains(child))
  {
    m_children.removeOne(child);
    child->m_parent = nullptr;
  }
}

const FlowConvertersTreeItem *FlowConvertersTreeItem::getChild(int row) const
{
  if (row < 0 || row >= m_children.size()) return nullptr;
  return m_children.at(row);
}

FlowConvertersTreeItem *FlowConvertersTreeItem::getChild(int row)
{
  if (row < 0 || row >= m_children.size()) return nullptr;
  return m_children.at(row);
}

int FlowConvertersTreeItem::getChildCount() const
{
  return static_cast<int>(m_children.count());
}

int FlowConvertersTreeItem::findChild(FlowConvertersTreeItem *child) const
{
  return static_cast<int>(m_children.indexOf(child));
}

/* ------------------ FlowConvertersTreeNodeFactoryContainerItem ----------------- */

FlowConvertersTreeNodeFactoryContainerItem::
  FlowConvertersTreeNodeFactoryContainerItem(
    node::ConverterFactoryContainer *factory_container)
    : m_factory_container(factory_container)
{}

QString FlowConvertersTreeNodeFactoryContainerItem::getName() const
{
  return m_factory_container->getName();
}

QIcon FlowConvertersTreeNodeFactoryContainerItem::getIcon() const
{
  return m_factory_container->getIcon();
}

node::ConverterFactoryContainer *
FlowConvertersTreeNodeFactoryContainerItem::getConverterFactoryContainer() const
{
  return m_factory_container;
}

/* ----------------------- FlowConvertersTreeNodeFactoryItem --------------------- */

FlowConvertersTreeNodeFactoryItem::FlowConvertersTreeNodeFactoryItem(
  node::ConverterFactory *factory)
    : m_factory(factory)
{}

QString FlowConvertersTreeNodeFactoryItem::getName() const
{
  return m_factory->getName();
}

QIcon FlowConvertersTreeNodeFactoryItem::getIcon() const
{
  return m_factory->getIcon();
}

node::ConverterFactory *
FlowConvertersTreeNodeFactoryItem::getConverterFactory() const
{
  return m_factory;
}

/* ---------------------------- FlowConvertersTreeModel -------------------------- */

FlowConvertersTreeModel::FlowConvertersTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
  connect(
    &PluginManager::getInstance(), &PluginManager::objectAdded, this,
    &FlowConvertersTreeModel::enabledPlugin);
  connect(
    &PluginManager::getInstance(), &PluginManager::objectRemoved, this,
    &FlowConvertersTreeModel::disabledPlugin);

  init();
}

FlowConvertersTreeModel::~FlowConvertersTreeModel()
{
  qDeleteAll(m_root_items);
}

Qt::ItemFlags FlowConvertersTreeModel::flags(const QModelIndex &index) const
{
  return QAbstractItemModel::flags(index);
}

QVariant FlowConvertersTreeModel::data(const QModelIndex &index, int role) const
{
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return QVariant{};

  auto item = static_cast<FlowConvertersTreeItem *>(index.internalPointer());
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

  FlowConvertersTreeItem *parent_item{nullptr};
  if (parent.isValid())
  {
    parent_item =
      static_cast<FlowConvertersTreeItem *>(parent.internalPointer());
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
    static_cast<FlowConvertersTreeItem *>(index.internalPointer());
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
    return static_cast<FlowConvertersTreeItem *>(parent.internalPointer())
      ->getChildCount();
}

int FlowConvertersTreeModel::columnCount(const QModelIndex &parent) const
{
  return 1;
}

void FlowConvertersTreeModel::init()
{
  auto factory_containers =
    PluginManager::getInstance().getObjects<node::ConverterFactoryContainer>();
  for (auto factory_container : factory_containers)
    enabledPlugin(factory_container);
}

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
