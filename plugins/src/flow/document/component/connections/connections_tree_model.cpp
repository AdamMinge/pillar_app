/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/connections/connections_tree_model.h"

#include "flow/document/command/change_connection.h"
#include "flow/document/command/change_layer.h"
#include "flow/document/document.h"
#include "flow/document/event/change_event.h"
#include "flow/document/event/connection_change_event.h"
#include "flow/document/event/layer_change_event.h"
#include "flow/document/flow/connection.h"
#include "flow/document/flow/flow.h"
#include "flow/document/flow/group_layer.h"
#include "flow/document/flow/layer.h"
#include "flow/document/flow/node_layer.h"
#include "flow/document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMimeData>
/* -------------------------------------------------------------------------- */

namespace flow {

/* --------------------------- ConnectionsTreeModel ------------------------- */

ConnectionsTreeModel::ConnectionsTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_document(nullptr), m_flow(nullptr) {}

ConnectionsTreeModel::~ConnectionsTreeModel() = default;

void ConnectionsTreeModel::setDocument(FlowDocument *flow_document) {
  if (m_document == flow_document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::event, this,
               &ConnectionsTreeModel::onEvent);
  }

  beginResetModel();
  m_document = flow_document;
  m_flow = m_document ? m_document->getFlow() : nullptr;
  endResetModel();

  if (m_document) {
    connect(m_document, &FlowDocument::event, this,
            &ConnectionsTreeModel::onEvent);
  }
}

FlowDocument *ConnectionsTreeModel::getDocument() const { return m_document; }

Qt::ItemFlags ConnectionsTreeModel::flags(const QModelIndex &index) const {
  return getFlags(index);
}

QVariant ConnectionsTreeModel::data(const QModelIndex &index, int role) const {
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

bool ConnectionsTreeModel::setData(const QModelIndex &index,
                                   const QVariant &value, int role) {
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

QVariant ConnectionsTreeModel::headerData(int section,
                                          Qt::Orientation orientation,
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

QModelIndex ConnectionsTreeModel::index(Layer *layer, int column) const {
  Q_ASSERT(layer);
  const auto group_layer = layer->getParent();
  if (!group_layer) return QModelIndex{};

  const auto row = group_layer->indexOf(layer);
  Q_ASSERT(row >= 0);

  return createIndex(row, column, layer);
}

QModelIndex ConnectionsTreeModel::index(Connection *connection,
                                        int column) const {
  Q_ASSERT(connection);
  const auto node_layer = connection->getParent();
  if (!node_layer) return QModelIndex{};

  const auto row = node_layer->indexOfConnection(connection);
  Q_ASSERT(row >= 0);

  return createIndex(row, column, connection);
}

QModelIndex ConnectionsTreeModel::index(int row, int column,
                                        const QModelIndex &parent) const {
  auto object = static_cast<Layer *>(m_flow->getRootLayer());
  if (parent.isValid()) object = static_cast<Layer *>(parent.internalPointer());

  if (object->isClassOrChild<GroupLayer>()) {
    auto group_layer = static_cast<GroupLayer *>(object);
    if (group_layer->count() > row)
      return createIndex(row, column, group_layer->at(row));
  } else if (object->isClassOrChild<NodeLayer>()) {
    auto node_layer = static_cast<NodeLayer *>(object);
    if (node_layer->connectionsCount() > row)
      return createIndex(row, column, node_layer->connectionAt(row));
  }

  return QModelIndex{};
}

QModelIndex ConnectionsTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex{};

  auto object = static_cast<Object *>(index.internalPointer());
  const auto type = object->getClassName();

  if (object->isClassOrChild<NodeLayer>()) {
    auto layer = static_cast<NodeLayer *>(object);
    return ConnectionsTreeModel::index(layer->getParent());
  } else if (object->isClassOrChild<Connection>()) {
    auto connection = static_cast<Connection *>(object);
    return ConnectionsTreeModel::index(connection->getParent());
  }

  return QModelIndex{};
}

int ConnectionsTreeModel::rowCount(const QModelIndex &parent) const {
  if (!m_document) return 0;

  if (!parent.isValid()) {
    auto root_layer = m_flow->getRootLayer();
    return static_cast<int>(root_layer->count());
  } else {
    auto object = static_cast<Object *>(parent.internalPointer());

    if (object->isClassOrChild<GroupLayer>()) {
      auto group_layer = static_cast<GroupLayer *>(object);
      return group_layer->count();
    } else if (object->isClassOrChild<NodeLayer>()) {
      auto node_layer = static_cast<NodeLayer *>(object);
      return node_layer->connectionsCount();
    }
  }

  return 0;
}

int ConnectionsTreeModel::columnCount(const QModelIndex &parent) const {
  return 2;
}

Layer *ConnectionsTreeModel::toLayer(const QModelIndex &index) const {
  if (!index.isValid()) return nullptr;

  auto object = static_cast<Object *>(index.internalPointer());
  if (object->isClassOrChild<Layer>()) {
    return static_cast<Layer *>(object);
  }

  return nullptr;
}

Connection *ConnectionsTreeModel::toConnection(const QModelIndex &index) const {
  if (!index.isValid()) return nullptr;

  auto object = static_cast<Object *>(index.internalPointer());
  if (object->isClassOrChild<Connection>()) {
    return static_cast<Connection *>(object);
  }

  return nullptr;
}

void ConnectionsTreeModel::onEvent(const ChangeEvent &event) {
  if (event.getType() == ConnectionEvent::type) {
    const auto connection_event = static_cast<const ConnectionEvent &>(event);
    switch (connection_event.getEvent()) {
      using enum ConnectionEvent::Event;

      case AboutToBeAdded: {
        beginInsertRows(index(connection_event.getNodeLayer()),
                        connection_event.getIndex(),
                        connection_event.getIndex());
        break;
      }

      case Added: {
        endInsertRows();
        break;
      }

      case AboutToBeRemoved: {
        beginRemoveRows(index(connection_event.getNodeLayer()),
                        connection_event.getIndex(),
                        connection_event.getIndex());
        break;
      }

      case Removed: {
        endRemoveRows();
        break;
      }
    }

  } else if (event.getType() == LayerEvent::type) {
    const auto layer_event = static_cast<const LayerEvent &>(event);
    switch (layer_event.getEvent()) {
      using enum LayerEvent::Event;

      case AboutToBeAdded: {
        beginInsertRows(index(layer_event.getGroupLayer()),
                        layer_event.getIndex(), layer_event.getIndex());
        break;
      }

      case Added: {
        endInsertRows();
        break;
      }

      case AboutToBeRemoved: {
        beginRemoveRows(index(layer_event.getGroupLayer()),
                        layer_event.getIndex(), layer_event.getIndex());
        break;
      }

      case Removed: {
        endRemoveRows();
        break;
      }
    }

  } else if (event.getType() == ConnectionsChangeEvent::type) {
    const auto connections_event =
        static_cast<const ConnectionsChangeEvent &>(event);
    const auto &connections = connections_event.getConnections();
    const auto properties = connections_event.getProperties();

    auto columns = QVarLengthArray<int, 3>{};
    if (properties & ConnectionsChangeEvent::Property::Name)
      columns.append(Column::NameColumn);
    if (properties & ConnectionsChangeEvent::Property::Visible)
      columns.append(Column::VisibleColumn);

    if (!columns.empty()) {
      auto [col_min, col_max] =
          std::minmax_element(columns.begin(), columns.end());

      for (auto connection : connections) {
        auto min_index = index(connection, *col_min);
        auto max_index = index(connection, *col_max);

        Q_EMIT dataChanged(min_index, max_index);
      }
    }

  } else if (event.getType() == LayersChangeEvent::type) {
    const auto layers_event = static_cast<const LayersChangeEvent &>(event);
    const auto &layers = layers_event.getLayers();
    const auto properties = layers_event.getProperties();

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
  }
}

Qt::ItemFlags ConnectionsTreeModel::getFlags(const QModelIndex &index) const {
  auto flags = QAbstractItemModel::flags(index);

  if (index.column() == Column::VisibleColumn) flags |= Qt::ItemIsUserCheckable;
  if (index.column() == Column::NameColumn) flags |= Qt::ItemIsEditable;

  const auto object = static_cast<Object *>(index.internalPointer());
  if (object->isClassOrChild<Connection>())
    flags |= Qt::ItemIsSelectable;
  else
    flags &= ~Qt::ItemIsSelectable;

  return flags;
}

QString ConnectionsTreeModel::getName(const QModelIndex &index) const {
  const auto object = static_cast<Object *>(index.internalPointer());
  return object->getName();
}

QIcon ConnectionsTreeModel::getIcon(const QModelIndex &index) const {
  const auto object = static_cast<Object *>(index.internalPointer());

  if (object->isClassOrChild<Layer>()) {
    auto factory = getObjectFactoryByClassName(object->getClassName());
    if (factory) return factory->getIcon();
  } else {
    return QIcon(icons::x32::Connection);
  }

  return QIcon{};
}

Qt::CheckState ConnectionsTreeModel::isVisible(const QModelIndex &index) const {
  const auto object = static_cast<Object *>(index.internalPointer());

  auto is_visible = false;
  if (object->isClassOrChild<Connection>()) {
    auto connection = static_cast<Connection *>(object);
    is_visible = connection->isVisible();
  } else if (object->isClassOrChild<Layer>()) {
    auto layer = static_cast<Layer *>(object);
    is_visible = layer->isVisible();
  }

  return is_visible ? Qt::Checked : Qt::Unchecked;
}

void ConnectionsTreeModel::setName(const QModelIndex &index,
                                   const QString &name) {
  const auto object = static_cast<Object *>(index.internalPointer());
  if (object->getName() == name) return;

  if (object->isClassOrChild<Connection>()) {
    m_document->getUndoStack()->push(new SetConnectionsName(
        m_document, {static_cast<Connection *>(object)}, name));
  } else if (object->isClassOrChild<Layer>()) {
    m_document->getUndoStack()->push(
        new SetLayersName(m_document, {static_cast<Layer *>(object)}, name));
  }
}

void ConnectionsTreeModel::setVisible(const QModelIndex &index,
                                      Qt::CheckState state) {
  const auto object = static_cast<Object *>(index.internalPointer());
  const auto visible = state == Qt::Checked;

  if (object->isClassOrChild<Connection>()) {
    m_document->getUndoStack()->push(new SetConnectionsVisible(
        m_document, {static_cast<Connection *>(object)}, visible));
  } else if (object->isClassOrChild<Layer>()) {
    m_document->getUndoStack()->push(new SetLayersVisible(
        m_document, {static_cast<Layer *>(object)}, visible));
  }
}

/* ---------------------- OnlyConnectionsFilterProxyModel ------------------- */

OnlyConnectionsFilterProxyModel::OnlyConnectionsFilterProxyModel(
    QObject *parent)
    : qtils::QtReverseProxyModel(parent) {}

OnlyConnectionsFilterProxyModel::~OnlyConnectionsFilterProxyModel() = default;

bool OnlyConnectionsFilterProxyModel::filterAcceptsRow(
    int source_row, const QModelIndex &source_parent) const {
  const auto index = sourceModel()->index(source_row, 0, source_parent);
  const auto object = static_cast<Object *>(index.internalPointer());

  const auto is_node_layer = object->isClassOrChild<NodeLayer>();
  const auto is_connection = object->isClassOrChild<Connection>();

  return is_node_layer || is_connection;
}

}  // namespace flow