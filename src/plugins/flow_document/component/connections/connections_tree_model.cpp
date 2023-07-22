/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/connections/connections_tree_model.h"

#include "flow_document/event/change_event.h"
#include "flow_document/flow/connection.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMimeData>
/* -------------------------------------------------------------------------- */

namespace flow_document {

ConnectionsTreeModel::ConnectionsTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_document(nullptr) {}

ConnectionsTreeModel::~ConnectionsTreeModel() = default;

void ConnectionsTreeModel::setDocument(FlowDocument *flow_document) {
  if (m_document == flow_document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::event, this,
               &ConnectionsTreeModel::onEvent);
  }

  beginResetModel();
  m_document = flow_document;
  endResetModel();

  if (m_document) {
    connect(m_document, &FlowDocument::event, this,
            &ConnectionsTreeModel::onEvent);
  }
}

FlowDocument *ConnectionsTreeModel::getDocument() const { return m_document; }

Qt::ItemFlags ConnectionsTreeModel::flags(const QModelIndex &index) const {
  auto flags = QAbstractItemModel::flags(index);
  if (index.column() == Column::NameColumn) flags |= Qt::ItemIsEditable;

  return flags;
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
  }

  return QVariant{};
}

bool ConnectionsTreeModel::setData(const QModelIndex &index,
                                   const QVariant &value, int role) {
  if (!index.isValid()) return false;

  switch (role) {
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
    default:
      return QVariant{};
  }
}

QModelIndex ConnectionsTreeModel::index(Connection *connection,
                                        int column) const {
  Q_ASSERT(connection);

  /*
  const auto group_layer = layer->getParent();
  if (!group_layer) return QModelIndex{};

  const auto row = group_layer->indexOf(layer);
  Q_ASSERT(row >= 0);

  return createIndex(row, column, connection);
  */
}

QModelIndex ConnectionsTreeModel::index(int row, int column,
                                        const QModelIndex &parent) const {
  /*
  auto parent_layer = m_flow->getRootLayer();
  if (parent.isValid())
    parent_layer = static_cast<GroupLayer *>(parent.internalPointer());

  if (parent_layer->size() <= row) return QModelIndex{};
  return createIndex(row, column, parent_layer->at(row));
  */
}

QModelIndex ConnectionsTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex{};

  /*
  auto child_item = static_cast<Connection *>(index.internalPointer());
  return ConnectionsTreeModel::index(child_item->getParent());
  */
}

int ConnectionsTreeModel::rowCount(const QModelIndex &parent) const {
  if (!m_document) return 0;
  return 0;

  /*
  if (!parent.isValid()) {
    auto root_layer = m_flow->getRootLayer();
    return static_cast<int>(root_layer->size());
  } else {
    auto layer = static_cast<Layer *>(parent.internalPointer());
    if (!layer->isClassOrChild<GroupLayer>()) return 0;

    auto group_layer = static_cast<GroupLayer *>(layer);
    return group_layer->size();
  }
  */
}

int ConnectionsTreeModel::columnCount(const QModelIndex &parent) const {
  return 1;
}

Connection *ConnectionsTreeModel::toConnection(const QModelIndex &index) const {
  if (!index.isValid()) return nullptr;
  return static_cast<Connection *>(index.internalPointer());
}

void ConnectionsTreeModel::onEvent(const ChangeEvent &event) {
  /*
  if (event.getType() == ConnectionEvent::type) {
    const auto &connection_event = static_cast<const ConnectionEvent &>(event);

    switch (connection_event.getEvent()) {
      using enum ConnectionEvent::Event;

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
    const auto &connections_event =
        static_cast<const ConnectionsChangeEvent &>(event);
    const auto &connections = connections_event.getConnections();
    const auto properties = connections_event.getProperties();

    auto columns = QVarLengthArray<int, 3>{};
    if (properties & ConnectionsChangeEvent::Property::Name)
      columns.append(Column::NameColumn);

    if (!columns.empty()) {
      auto [col_min, col_max] =
          std::minmax_element(columns.begin(), columns.end());

      for (auto connection : connections) {
        auto min_index = index(connection, *col_min);
        auto max_index = index(connection, *col_max);

        Q_EMIT dataChanged(min_index, max_index);
      }
    }
  }
  */
}

QString ConnectionsTreeModel::getName(const QModelIndex &index) const {
  auto connection = static_cast<Connection *>(index.internalPointer());
  return connection->getName();
}

QIcon ConnectionsTreeModel::getIcon(const QModelIndex &index) const {
  /*
  auto layer = static_cast<Layer *>(index.internalPointer());
  auto factory = getObjectFactoryByClassName(layer->getClassName());
  if (factory) return factory->getIcon();
  */
  return QIcon{};
}

void ConnectionsTreeModel::setName(const QModelIndex &index,
                                   const QString &name) {
  /*
  auto layer = static_cast<Layer *>(index.internalPointer());
  if (layer->getName() == name) return;

  m_document->getUndoStack()->push(
  new SetLayersName(m_document, {layer}, name));
  */
}

}  // namespace flow_document