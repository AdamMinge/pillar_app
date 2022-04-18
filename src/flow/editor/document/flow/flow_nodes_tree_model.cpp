/* ------------------------------------ Qt ---------------------------------- */
#include <QMimeData>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/flow/flow_nodes_tree_model.h"
#include "flow/editor/plugin_manager.h"
/* ----------------------------------- Node --------------------------------- */
#include "flow/modules/node/node_factory.h"
#include "flow/modules/node/node_factory_container.h"
/* -------------------------------------------------------------------------- */

/* ---------------------------- FlowNodesTreeItem --------------------------- */

FlowNodesTreeItem::FlowNodesTreeItem() : m_parent(nullptr) {}

FlowNodesTreeItem::~FlowNodesTreeItem() { qDeleteAll(m_children); }

FlowNodesTreeItem *FlowNodesTreeItem::getParent() const { return m_parent; }

void FlowNodesTreeItem::addChild(FlowNodesTreeItem *child)
{
  if (!m_children.contains(child))
  {
    if (child->m_parent) child->m_parent->removeChild(child);

    m_children.append(child);
    child->m_parent = this;
  }
}

void FlowNodesTreeItem::removeChild(FlowNodesTreeItem *child)
{
  if (m_children.contains(child))
  {
    m_children.removeOne(child);
    child->m_parent = nullptr;
  }
}

const FlowNodesTreeItem *FlowNodesTreeItem::getChild(int row) const
{
  if (row < 0 || row >= m_children.size()) return nullptr;
  return m_children.at(row);
}

FlowNodesTreeItem *FlowNodesTreeItem::getChild(int row)
{
  if (row < 0 || row >= m_children.size()) return nullptr;
  return m_children.at(row);
}

int FlowNodesTreeItem::getChildCount() const
{
  return static_cast<int>(m_children.count());
}

int FlowNodesTreeItem::findChild(FlowNodesTreeItem *child) const
{
  return static_cast<int>(m_children.indexOf(child));
}

/* ------------------ FlowNodesTreeNodeFactoryContainerItem ----------------- */

FlowNodesTreeNodeFactoryContainerItem::FlowNodesTreeNodeFactoryContainerItem(
  node::NodeFactoryContainer *factory_container)
    : m_factory_container(factory_container)
{}

QString FlowNodesTreeNodeFactoryContainerItem::getName() const
{
  return m_factory_container->getName();
}

QIcon FlowNodesTreeNodeFactoryContainerItem::getIcon() const
{
  return m_factory_container->getIcon();
}

Qt::ItemFlags FlowNodesTreeNodeFactoryContainerItem::flags() const
{
  return Qt::NoItemFlags;
}

node::NodeFactoryContainer *
FlowNodesTreeNodeFactoryContainerItem::getNodeFactoryContainer() const
{
  return m_factory_container;
}

/* ----------------------- FlowNodesTreeNodeFactoryItem --------------------- */

FlowNodesTreeNodeFactoryItem::FlowNodesTreeNodeFactoryItem(
  node::NodeFactory *factory)
    : m_factory(factory)
{}

QString FlowNodesTreeNodeFactoryItem::getName() const
{
  return m_factory->getName();
}

QIcon FlowNodesTreeNodeFactoryItem::getIcon() const
{
  return m_factory->getIcon();
}

Qt::ItemFlags FlowNodesTreeNodeFactoryItem::flags() const
{
  return Qt::ItemIsDragEnabled;
}

node::NodeFactory *FlowNodesTreeNodeFactoryItem::getNodeFactory() const
{
  return m_factory;
}

/* ---------------------------- FlowNodesTreeModel -------------------------- */

FlowNodesTreeModel::FlowNodesTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
  connect(
    &PluginManager::getInstance(), &PluginManager::objectAdded, this,
    &FlowNodesTreeModel::enabledPlugin);
  connect(
    &PluginManager::getInstance(), &PluginManager::objectRemoved, this,
    &FlowNodesTreeModel::disabledPlugin);

  init();
}

FlowNodesTreeModel::~FlowNodesTreeModel() { qDeleteAll(m_root_items); }

Qt::ItemFlags FlowNodesTreeModel::flags(const QModelIndex &index) const
{
  auto item = static_cast<FlowNodesTreeItem *>(index.internalPointer());
  return QAbstractItemModel::flags(index) | item->flags();
}

QVariant FlowNodesTreeModel::data(const QModelIndex &index, int role) const
{
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return QVariant{};

  auto item = static_cast<FlowNodesTreeItem *>(index.internalPointer());
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

QVariant FlowNodesTreeModel::headerData(
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

QModelIndex
FlowNodesTreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent)) return QModelIndex{};

  FlowNodesTreeItem *parent_item{nullptr};
  if (parent.isValid())
  {
    parent_item = static_cast<FlowNodesTreeItem *>(parent.internalPointer());
    return createIndex(row, column, parent_item->getChild(row));
  } else
  {
    return createIndex(row, column, m_root_items.at(row));
  }
}

QModelIndex FlowNodesTreeModel::parent(const QModelIndex &index) const
{
  if (!index.isValid()) return QModelIndex{};

  auto child_item = static_cast<FlowNodesTreeItem *>(index.internalPointer());
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

int FlowNodesTreeModel::rowCount(const QModelIndex &parent) const
{
  if (parent.column() > 0) return 0;

  if (!parent.isValid()) return static_cast<int>(m_root_items.size());
  else
    return static_cast<FlowNodesTreeItem *>(parent.internalPointer())
      ->getChildCount();
}

int FlowNodesTreeModel::columnCount(const QModelIndex &parent) const
{
  return 1;
}

QMimeData *FlowNodesTreeModel::mimeData(const QModelIndexList &indexes) const
{
  auto mime_data = new QMimeData;
  mime_data->setData(QLatin1String("flow/node"), "");
  // TODO Implementation

  return mime_data;
}

QStringList FlowNodesTreeModel::mimeTypes() const
{
  return QStringList{} << QLatin1String("flow/node");
}

void FlowNodesTreeModel::init()
{
  auto factory_containers =
    PluginManager::getInstance().getObjects<node::NodeFactoryContainer>();
  for (auto factory_container : factory_containers)
    enabledPlugin(factory_container);
}

void FlowNodesTreeModel::enabledPlugin(QObject *object)
{
  if (
    auto factory_container = qobject_cast<node::NodeFactoryContainer *>(object))
  {
    auto factory_container_item =
      std::make_unique<FlowNodesTreeNodeFactoryContainerItem>(
        factory_container);

    for (auto &factory : *factory_container)
    {
      factory_container_item->addChild(
        new FlowNodesTreeNodeFactoryItem(factory.get()));
    }

    auto index_to_insert = static_cast<int>(m_root_items.count());

    beginInsertRows(QModelIndex{}, index_to_insert, index_to_insert);
    m_root_items.insert(index_to_insert, factory_container_item.release());
    endInsertRows();
  }
}

void FlowNodesTreeModel::disabledPlugin(QObject *object)
{
  if (
    auto factory_container = qobject_cast<node::NodeFactoryContainer *>(object))
  {
    auto found_root = std::find_if(
      m_root_items.begin(), m_root_items.end(), [factory_container](auto item) {
        return item->getNodeFactoryContainer() == factory_container;
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
