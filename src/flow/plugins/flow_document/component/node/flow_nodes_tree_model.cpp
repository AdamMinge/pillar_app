/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/component/node/flow_nodes_tree_model.h"

#include "flow/plugins/flow_document/node/node_factory.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMimeData>
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

/* ---------------------------- FlowNodesTreeItem --------------------------- */

FlowNodesTreeItem::FlowNodesTreeItem() : m_parent(nullptr) {}

FlowNodesTreeItem::~FlowNodesTreeItem() { qDeleteAll(m_children); }

FlowNodesTreeItem *FlowNodesTreeItem::getParent() const { return m_parent; }

void FlowNodesTreeItem::addChild(FlowNodesTreeItem *child) {
  if (!m_children.contains(child)) {
    if (child->m_parent) child->m_parent->removeChild(child);

    m_children.append(child);
    child->m_parent = this;
  }
}

void FlowNodesTreeItem::removeChild(FlowNodesTreeItem *child) {
  if (m_children.contains(child)) {
    m_children.removeOne(child);
    child->m_parent = nullptr;
  }
}

const FlowNodesTreeItem *FlowNodesTreeItem::getChild(int row) const {
  if (row < 0 || row >= m_children.size()) return nullptr;
  return m_children.at(row);
}

FlowNodesTreeItem *FlowNodesTreeItem::getChild(int row) {
  if (row < 0 || row >= m_children.size()) return nullptr;
  return m_children.at(row);
}

int FlowNodesTreeItem::getChildCount() const {
  return static_cast<int>(m_children.count());
}

int FlowNodesTreeItem::findChild(FlowNodesTreeItem *child) const {
  return static_cast<int>(m_children.indexOf(child));
}

/* ------------------------ FlowNodesTreeFactoriesItem ---------------------- */

FlowNodesTreeFactoriesItem::FlowNodesTreeFactoriesItem(NodeFactories *factories)
    : m_factories(factories) {
  for (const auto &node_id : factories->getNodeIds())
    addChild(new FlowNodesTreeFactoryItem(factories->getFactory(node_id)));
}

QString FlowNodesTreeFactoriesItem::getName() const {
  return m_factories->getName();
}

QIcon FlowNodesTreeFactoriesItem::getIcon() const {
  return QIcon(":/plugins/document/flow/images/32x32/factories.png");
}

Qt::ItemFlags FlowNodesTreeFactoriesItem::flags() const {
  return Qt::NoItemFlags;
}

NodeFactories *FlowNodesTreeFactoriesItem::getNodeFactories() const {
  return m_factories;
}

/* ------------------------- FlowNodesTreeFactoryItem ----------------------- */

FlowNodesTreeFactoryItem::FlowNodesTreeFactoryItem(NodeFactory *factory)
    : m_factory(factory) {}

QString FlowNodesTreeFactoryItem::getName() const {
  return m_factory->getName();
}

QIcon FlowNodesTreeFactoryItem::getIcon() const {
  return QIcon(":/plugins/document/flow/images/32x32/node_factory.png");
}

Qt::ItemFlags FlowNodesTreeFactoryItem::flags() const {
  return Qt::ItemIsDragEnabled;
}

NodeFactory *FlowNodesTreeFactoryItem::getNodeFactory() const {
  return m_factory;
}

/* ---------------------------- FlowNodesTreeModel -------------------------- */

FlowNodesTreeModel::FlowNodesTreeModel(QObject *parent)
    : QAbstractItemModel(parent) {
  loadObjects();
}

FlowNodesTreeModel::~FlowNodesTreeModel() { qDeleteAll(m_root_items); }

Qt::ItemFlags FlowNodesTreeModel::flags(const QModelIndex &index) const {
  auto item = static_cast<FlowNodesTreeItem *>(index.internalPointer());
  return QAbstractItemModel::flags(index) | item->flags();
}

QVariant FlowNodesTreeModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return QVariant{};

  auto item = static_cast<FlowNodesTreeItem *>(index.internalPointer());
  switch (role) {
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

QVariant FlowNodesTreeModel::headerData(int section,
                                        Qt::Orientation orientation,
                                        int role) const {
  if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
    return QVariant{};

  switch (section)  // NOLINT(hicpp-multiway-paths-covered)
  {
    case Column::NameColumn:
      return tr("Name");
    default:
      return QVariant{};
  }
}

QModelIndex FlowNodesTreeModel::index(int row, int column,
                                      const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex{};

  FlowNodesTreeItem *parent_item{nullptr};
  if (parent.isValid()) {
    parent_item = static_cast<FlowNodesTreeItem *>(parent.internalPointer());
    return createIndex(row, column, parent_item->getChild(row));
  } else {
    return createIndex(row, column, m_root_items.at(row));
  }
}

QModelIndex FlowNodesTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex{};

  auto child_item = static_cast<FlowNodesTreeItem *>(index.internalPointer());
  auto item = child_item->getParent();

  if (m_root_items.contains(item)) {
    auto row = static_cast<int>(m_root_items.indexOf(item));
    return createIndex(row, 0, item);
  } else {
    auto parent_item = item ? item->getParent() : nullptr;
    if (!parent_item) return QModelIndex{};

    auto row = parent_item->findChild(item);
    return createIndex(row, 0, item);
  }
}

int FlowNodesTreeModel::rowCount(const QModelIndex &parent) const {
  if (parent.column() > 0) return 0;

  if (!parent.isValid())
    return static_cast<int>(m_root_items.size());
  else
    return static_cast<FlowNodesTreeItem *>(parent.internalPointer())
        ->getChildCount();
}

int FlowNodesTreeModel::columnCount(const QModelIndex &parent) const {
  return 1;
}

QMimeData *FlowNodesTreeModel::mimeData(const QModelIndexList &indexes) const {
  auto mime_data = new QMimeData;
  mime_data->setData(QLatin1String("flow/node"), createMimeData(indexes));

  return mime_data;
}

QStringList FlowNodesTreeModel::mimeTypes() const {
  return QStringList{} << QLatin1String("flow/node");
}

void FlowNodesTreeModel::addedObject(NodeFactories *factories) {
  auto factories_item = std::make_unique<FlowNodesTreeFactoriesItem>(factories);
  auto index_to_insert = static_cast<int>(m_root_items.count());

  beginInsertRows(QModelIndex{}, index_to_insert, index_to_insert);
  m_root_items.insert(index_to_insert, factories_item.release());
  endInsertRows();
}

void FlowNodesTreeModel::removedObject(NodeFactories *factories) {
  auto found_root = std::find_if(
      m_root_items.begin(), m_root_items.end(),
      [factories](auto item) { return item->getNodeFactories() == factories; });

  if (found_root != m_root_items.end()) {
    auto index_to_remove =
        static_cast<int>(std::distance(m_root_items.begin(), found_root));

    beginRemoveRows(QModelIndex{}, index_to_remove, index_to_remove);
    m_root_items.remove(index_to_remove);
    endRemoveRows();
  }
}

QByteArray FlowNodesTreeModel::createMimeData(
    const QModelIndexList &indexes) const {
  auto nodes = QStringList{};
  for (auto index : indexes) {
    auto node_factory =
        static_cast<FlowNodesTreeFactoryItem *>(index.internalPointer())
            ->getNodeFactory();
    nodes << node_factory->getNodeId();
  }

  return nodes.join(';').toLocal8Bit();
}

}  // namespace plugin::flow_document