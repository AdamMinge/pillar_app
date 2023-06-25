/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/nodes/nodes_tree_model.h"

#include "flow_document/command/change_layer.h"
#include "flow_document/command/change_node.h"
#include "flow_document/event/change_event.h"
#include "flow_document/event/layer_change_event.h"
#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/node.h"
#include "flow_document/flow/node_layer.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------ NodesTreeModel ---------------------------- */

NodesTreeModel::NodesTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_document(nullptr), m_flow(nullptr) {}

NodesTreeModel::~NodesTreeModel() = default;

void NodesTreeModel::setDocument(FlowDocument *flow_document) {
  if (m_document == flow_document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::event, this,
               &NodesTreeModel::onEvent);
  }

  beginResetModel();
  m_document = flow_document;
  m_flow = m_document ? m_document->getFlow() : nullptr;
  endResetModel();

  if (m_document) {
    connect(m_document, &FlowDocument::event, this, &NodesTreeModel::onEvent);
  }
}

FlowDocument *NodesTreeModel::getDocument() const { return m_document; }

Qt::ItemFlags NodesTreeModel::flags(const QModelIndex &index) const {
  auto flags = QAbstractItemModel::flags(index);

  if (index.column() == Column::VisibleColumn) flags |= Qt::ItemIsUserCheckable;
  if (index.column() == Column::NameColumn) flags |= Qt::ItemIsEditable;

  return flags;
}

QVariant NodesTreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return {};

  switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole: {
      if (index.column() == Column::NameColumn) return getName(index);
      break;
    }

    case Qt::DecorationRole: {
      if (index.column() == Column::NameColumn) return getIcon(index);
      break;
    }

    case Qt::CheckStateRole: {
      if (index.column() == Column::VisibleColumn) return isVisible(index);
      break;
    }
  }

  return QVariant{};
}

bool NodesTreeModel::setData(const QModelIndex &index, const QVariant &value,
                             int role) {
  if (!index.isValid()) return false;

  switch (role) {
    case Qt::CheckStateRole: {
      if (index.column() == Column::VisibleColumn) {
        setVisible(index, static_cast<Qt::CheckState>(value.toInt()));
      }
      return true;
    }

    case Qt::EditRole: {
      if (index.column() == Column::NameColumn) {
        setName(index, value.toString());
      }
      return true;
    }
  }

  return false;
}

QVariant NodesTreeModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
  if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
    return QVariant{};

  switch (section) {
    case Column::NameColumn:
      return tr("Name");
    case Column::VisibleColumn:
      return tr("Visible");
    default:
      return QVariant{};
  }
}

QModelIndex NodesTreeModel::index(Layer *layer, int column) const {
  Q_ASSERT(layer);
  const auto group_layer = layer->getParent();
  if (!group_layer) return QModelIndex{};

  const auto row = group_layer->indexOf(layer);
  Q_ASSERT(row >= 0);

  return createIndex(row, column, layer);
}

QModelIndex NodesTreeModel::index(Node *node, int column) const {
  Q_ASSERT(node);
  const auto node_layer = node->getParent();
  if (!node_layer) return QModelIndex{};

  const auto row = node_layer->indexOf(node);
  Q_ASSERT(row >= 0);

  return createIndex(row, column, node);
}

QModelIndex NodesTreeModel::index(int row, int column,
                                  const QModelIndex &parent) const {
  auto object = static_cast<Object *>(m_flow->getRootLayer());
  if (parent.isValid())
    object = static_cast<Object *>(parent.internalPointer());

  if (object->isClassOrChild<GroupLayer>()) {
    auto group_layer = static_cast<GroupLayer *>(object);
    if (group_layer->size() > row)
      return createIndex(row, column, group_layer->at(row));
  } else if (object->isClassOrChild<NodeLayer>()) {
    auto node_layer = static_cast<NodeLayer *>(object);
    if (node_layer->size() > row)
      return createIndex(row, column, node_layer->at(row));
  }

  return QModelIndex{};
}

QModelIndex NodesTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex{};

  auto object = static_cast<Object *>(index.internalPointer());
  const auto type = object->getClassName();

  if (object->isClassOrChild<Layer>()) {
    auto layer = static_cast<Layer *>(object);
    return NodesTreeModel::index(layer->getParent());
  } else if (object->isClassOrChild<Node>()) {
    auto node = static_cast<Node *>(object);
    return NodesTreeModel::index(node->getParent());
  }

  return QModelIndex{};
}

int NodesTreeModel::rowCount(const QModelIndex &parent) const {
  if (!m_document) return 0;

  if (!parent.isValid()) {
    auto root_layer = m_flow->getRootLayer();
    return static_cast<int>(root_layer->size());
  } else {
    auto object = static_cast<Object *>(parent.internalPointer());

    if (object->isClassOrChild<GroupLayer>()) {
      auto group_layer = static_cast<GroupLayer *>(object);
      return group_layer->size();
    } else if (object->isClassOrChild<NodeLayer>()) {
      auto node_layer = static_cast<NodeLayer *>(object);
      return node_layer->size();
    }
  }

  return 0;
}

int NodesTreeModel::columnCount(const QModelIndex &parent) const { return 2; }

Layer *NodesTreeModel::toLayer(const QModelIndex &index) const {
  if (!index.isValid()) return nullptr;

  auto object = static_cast<Object *>(index.internalPointer());
  if (object->isClassOrChild<Layer>()) {
    return static_cast<Layer *>(object);
  }

  return nullptr;
}

Node *NodesTreeModel::toNode(const QModelIndex &index) const {
  if (!index.isValid()) return nullptr;

  auto object = static_cast<Object *>(index.internalPointer());
  if (object->isClassOrChild<Node>()) {
    return static_cast<Node *>(object);
  }

  return nullptr;
}

void NodesTreeModel::onEvent(const ChangeEvent &event) {
  switch (event.getType()) {
    using enum ChangeEvent::Type;

    case NodeAboutToBeAdded: {
      const auto &e = static_cast<const NodeEvent &>(event);
      beginInsertRows(index(e.getNodeLayer()), e.getIndex(), e.getIndex());
      break;
    }

    case LayerAboutToBeAdded: {
      const auto &e = static_cast<const LayerEvent &>(event);
      beginInsertRows(index(e.getGroupLayer()), e.getIndex(), e.getIndex());
      break;
    }

    case LayerAdded:
    case NodeAdded: {
      endInsertRows();
      break;
    }

    case NodeAboutToBeRemoved: {
      const auto &e = static_cast<const NodeEvent &>(event);
      beginRemoveRows(index(e.getNodeLayer()), e.getIndex(), e.getIndex());
      break;
    }

    case LayerAboutToBeRemoved: {
      const auto &e = static_cast<const LayerEvent &>(event);
      beginRemoveRows(index(e.getGroupLayer()), e.getIndex(), e.getIndex());
      break;
    }

    case LayerRemoved:
    case NodeRemoved: {
      endRemoveRows();
      break;
    }

    case LayersChanged: {
      const auto &e = static_cast<const LayersChangeEvent &>(event);
      const auto &layers = e.getLayers();
      const auto properties = e.getProperties();

      auto columns = QVarLengthArray<int, 3>{};
      if (properties & LayersChangeEvent::Property::Name)
        columns.append(Column::NameColumn);
      if (properties & LayersChangeEvent::Property::Visible)
        columns.append(Column::VisibleColumn);

      if (!columns.empty()) {
        auto [col_min, col_max] =
            std::minmax_element(columns.begin(), columns.end());

        for (auto layer : layers) {
          auto min_index = index(layer, *col_min);
          auto max_index = index(layer, *col_max);

          Q_EMIT dataChanged(min_index, max_index);
        }
      }

      break;
    }

    case NodesChanged: {
      const auto &e = static_cast<const NodesChangeEvent &>(event);
      const auto &nodes = e.getNodes();
      const auto properties = e.getProperties();

      auto columns = QVarLengthArray<int, 3>{};
      if (properties & NodesChangeEvent::Property::Name)
        columns.append(Column::NameColumn);
      if (properties & NodesChangeEvent::Property::Visible)
        columns.append(Column::VisibleColumn);

      if (!columns.empty()) {
        auto [col_min, col_max] =
            std::minmax_element(columns.begin(), columns.end());

        for (auto node : nodes) {
          auto min_index = index(node, *col_min);
          auto max_index = index(node, *col_max);

          Q_EMIT dataChanged(min_index, max_index);
        }
      }

      break;
    }
  }
}

QString NodesTreeModel::getName(const QModelIndex &index) const {
  const auto object = static_cast<Object *>(index.internalPointer());
  const auto type = object->getClassName();

  if (object->isClassOrChild<Layer>()) {
    auto layer = static_cast<Layer *>(object);
    return layer->getName();
  } else if (object->isClassOrChild<Node>()) {
    auto node = static_cast<Node *>(object);
    return node->getName();
  }

  return QString{};
}

QIcon NodesTreeModel::getIcon(const QModelIndex &index) const {
  const auto object = static_cast<Object *>(index.internalPointer());
  auto factory = getObjectFactoryByClassName(object->getClassName());
  if (factory) return factory->getIcon();

  return QIcon{};
}

Qt::CheckState NodesTreeModel::isVisible(const QModelIndex &index) const {
  const auto object = static_cast<Object *>(index.internalPointer());
  const auto type = object->getClassName();
  auto visible = true;

  if (object->isClassOrChild<Layer>()) {
    auto layer = static_cast<Layer *>(object);
    visible = layer->isVisible();
  } else if (object->isClassOrChild<Node>()) {
    auto node = static_cast<Node *>(object);
    visible = node->isVisible();
  }

  return visible ? Qt::Checked : Qt::Unchecked;
}

void NodesTreeModel::setName(const QModelIndex &index, const QString &name) {
  const auto object = static_cast<Object *>(index.internalPointer());
  const auto type = object->getClassName();

  if (object->isClassOrChild<Layer>()) {
    auto layer = static_cast<Layer *>(object);
    m_document->getUndoStack()->push(
        new SetLayersName(m_document, {layer}, name));
  } else if (object->isClassOrChild<Node>()) {
    auto node = static_cast<Node *>(object);
    m_document->getUndoStack()->push(
        new SetNodesName(m_document, {node}, name));
  }
}

void NodesTreeModel::setVisible(const QModelIndex &index,
                                Qt::CheckState state) {
  const auto object = static_cast<Object *>(index.internalPointer());
  const auto type = object->getClassName();
  const auto visible = state == Qt::Checked;

  if (object->isClassOrChild<Layer>()) {
    auto layer = static_cast<Layer *>(object);
    m_document->getUndoStack()->push(
        new SetLayersVisible(m_document, {layer}, visible));
  } else if (object->isClassOrChild<Node>()) {
    auto node = static_cast<Node *>(object);
    m_document->getUndoStack()->push(
        new SetNodesVisible(m_document, {node}, visible));
  }
}

/* ------------------------- OnlyNodesFilterProxyModel ---------------------- */

OnlyNodesFilterProxyModel::OnlyNodesFilterProxyModel(QObject *parent)
    : utils::QtReverseProxyModel(parent) {}

OnlyNodesFilterProxyModel::~OnlyNodesFilterProxyModel() = default;

bool OnlyNodesFilterProxyModel::filterAcceptsRow(
    int source_row, const QModelIndex &source_parent) const {
  const auto index = sourceModel()->index(source_row, 0, source_parent);
  const auto object = static_cast<Object *>(index.internalPointer());

  const auto is_node_layer = object->isClassOrChild<NodeLayer>();
  const auto is_node = object->isClassOrChild<Node>();

  return is_node_layer || is_node;
}

}  // namespace flow_document