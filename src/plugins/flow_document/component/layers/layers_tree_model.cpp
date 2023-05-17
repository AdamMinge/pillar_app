/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/layers/layers_tree_model.h"

#include "flow_document/command/change_layer.h"
#include "flow_document/event/change_event.h"
#include "flow_document/event/layer_change_event.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

LayersTreeModel::LayersTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_document(nullptr), m_flow(nullptr) {}

LayersTreeModel::~LayersTreeModel() = default;

void LayersTreeModel::setDocument(FlowDocument *flow_document) {
  if (m_document == flow_document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::event, this,
               &LayersTreeModel::onEvent);
  }

  beginResetModel();
  m_document = flow_document;
  m_flow = m_document ? m_document->getFlow() : nullptr;
  endResetModel();

  if (m_document) {
    connect(m_document, &FlowDocument::event, this, &LayersTreeModel::onEvent);
  }
}

FlowDocument *LayersTreeModel::getDocument() const { return m_document; }

Qt::ItemFlags LayersTreeModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;

  auto flags = QAbstractItemModel::flags(index);

  if (index.column() == Column::VisibleColumn ||
      index.column() == Column::LockedColumn)
    flags |= Qt::ItemIsUserCheckable;

  if (index.column() == Column::NameColumn) flags |= Qt::ItemIsEditable;

  return flags;
}

QVariant LayersTreeModel::data(const QModelIndex &index, int role) const {
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
      if (index.column() == Column::VisibleColumn)
        return isVisible(index);
      else if (index.column() == Column::LockedColumn)
        return isLocked(index);

      break;
    }
  }

  return QVariant{};
}

bool LayersTreeModel::setData(const QModelIndex &index, const QVariant &value,
                              int role) {
  if (!index.isValid()) return false;

  switch (role) {
    case Qt::CheckStateRole: {
      if (index.column() == Column::VisibleColumn) {
        setVisible(index, static_cast<Qt::CheckState>(value.toInt()));
      } else if (index.column() == Column::LockedColumn) {
        setLocked(index, static_cast<Qt::CheckState>(value.toInt()));
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

QVariant LayersTreeModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
  if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
    return QVariant{};

  switch (section) {
    case Column::NameColumn:
      return tr("Name");
    case Column::VisibleColumn:
      return tr("Visible");
    case Column::LockedColumn:
      return tr("Locked");
    default:
      return QVariant{};
  }
}

QModelIndex LayersTreeModel::index(int row, int column,
                                   const QModelIndex &parent) const {
  GroupLayer *parent_item{nullptr};
  if (parent.isValid()) {
    parent_item = static_cast<GroupLayer *>(parent.internalPointer());
    return createIndex(row, column, parent_item->at(row));
  } else {
    auto root_layer = m_flow->getRootLayer();
    return createIndex(row, column, root_layer->at(row));
  }
}

QModelIndex LayersTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex{};

  auto child_item = static_cast<Layer *>(index.internalPointer());
  auto item = child_item->getParent();

  if (item) {
    auto parent_item = item->getParent();
    auto row = parent_item ? parent_item->indexOf(item) : 0;
    return createIndex(row, 0, item);
  }

  return QModelIndex{};
}

int LayersTreeModel::rowCount(const QModelIndex &parent) const {
  if (!m_document) return 0;

  if (!parent.isValid()) {
    auto root_layer = m_flow->getRootLayer();
    return static_cast<int>(root_layer->size());
  } else {
    auto layer = static_cast<Layer *>(parent.internalPointer());
    if (layer->getLayerType() == Layer::LayerType::GroupLayer) {
      auto group_layer = static_cast<GroupLayer *>(layer);
      return group_layer->size();
    }

    return 0;
  }
}

int LayersTreeModel::columnCount(const QModelIndex &parent) const { return 3; }

void LayersTreeModel::onEvent(const ChangeEvent &event) {
  switch (event.getType()) {
    using enum ChangeEvent::Type;

    case LayerAboutToBeAdded: {
      const auto &e = static_cast<const LayerEvent &>(event);
      beginInsertRows(index(e.getGroupLayer()), e.getIndex(), e.getIndex());
      break;
    }

    case LayerAdded: {
      endInsertRows();
      break;
    }

    case LayerAboutToBeRemoved: {
      const auto &e = static_cast<const LayerEvent &>(event);
      beginRemoveRows(index(e.getGroupLayer()), e.getIndex(), e.getIndex());
      break;
    }

    case LayerRemoved: {
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
      if (properties & LayersChangeEvent::Property::Locked)
        columns.append(Column::LockedColumn);

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
  }
}

QModelIndex LayersTreeModel::index(Layer *layer, int column) const {
  Q_ASSERT(layer);
  const auto group_layer = layer->getParent();
  if (!group_layer) return QModelIndex{};

  const auto row = group_layer->indexOf(layer);
  Q_ASSERT(row >= 0);

  return createIndex(row, column, layer);
}

QString LayersTreeModel::getName(const QModelIndex &index) const {
  auto layer = static_cast<Layer *>(index.internalPointer());
  return layer->getName();
}

QIcon LayersTreeModel::getIcon(const QModelIndex &index) const {
  auto layer = static_cast<Layer *>(index.internalPointer());
  switch (layer->getLayerType()) {
    case Layer::LayerType::GroupLayer:
      return QIcon(icons::x32::GroupLayer);

    case Layer::LayerType::NodeLayer:
      return QIcon(icons::x32::NodeLayer);
  }

  return QIcon{};
}

Qt::CheckState LayersTreeModel::isVisible(const QModelIndex &index) const {
  const auto layer = static_cast<Layer *>(index.internalPointer());
  return layer->isVisible() ? Qt::Checked : Qt::Unchecked;
}

Qt::CheckState LayersTreeModel::isLocked(const QModelIndex &index) const {
  const auto layer = static_cast<Layer *>(index.internalPointer());
  return layer->isLocked() ? Qt::Checked : Qt::Unchecked;
}

void LayersTreeModel::setName(const QModelIndex &index, const QString &name) {
  auto layer = static_cast<Layer *>(index.internalPointer());
  if (layer->getName() == name) return;

  m_document->getUndoStack()->push(new SetLayerName(m_document, layer, name));
}

void LayersTreeModel::setVisible(const QModelIndex &index,
                                 Qt::CheckState state) {
  auto layer = static_cast<Layer *>(index.internalPointer());
  const auto visible = state == Qt::Checked;
  m_document->getUndoStack()->push(
      new SetLayersVisible(m_document, {layer}, visible));
}

void LayersTreeModel::setLocked(const QModelIndex &index,
                                Qt::CheckState state) {
  auto layer = static_cast<Layer *>(index.internalPointer());
  const auto locked = state == Qt::Checked;
  m_document->getUndoStack()->push(
      new SetLayersLocked(m_document, {layer}, locked));
}

}  // namespace flow_document