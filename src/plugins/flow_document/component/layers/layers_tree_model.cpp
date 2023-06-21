/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/layers/layers_tree_model.h"

#include "flow_document/command/change_layer.h"
#include "flow_document/command/reparent_layer.h"
#include "flow_document/event/change_event.h"
#include "flow_document/event/layer_change_event.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/layer_iterator.h"
#include "flow_document/flow/node_layer.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMimeData>
/* -------------------------------------------------------------------------- */

namespace flow_document {

[[nodiscard]] QList<Layer *> getLayers(
    FlowDocument *document, const QList<qsizetype> &hierarchical_ids) {
  auto root = document ? document->getFlow()->getRootLayer() : nullptr;
  if (!root) return {};

  auto layers = getLayersByHierarchicalIds(root, hierarchical_ids);
  Q_ASSERT(!layers.empty());
  return layers;
}

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
  auto flags = QAbstractItemModel::flags(index);

  if (index.column() == Column::VisibleColumn ||
      index.column() == Column::LockedColumn)
    flags |= Qt::ItemIsUserCheckable;

  if (index.column() == Column::NameColumn) flags |= Qt::ItemIsEditable;

  auto layer = index.isValid() ? toLayer(index) : m_flow->getRootLayer();
  if (layer) flags |= Qt::ItemIsDragEnabled;
  if (layer && layer->isClassOrChild(GroupLayer::getStaticClassName()))
    flags |= Qt::ItemIsDropEnabled;

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

QModelIndex LayersTreeModel::index(Layer *layer, int column) const {
  Q_ASSERT(layer);
  const auto group_layer = layer->getParent();
  if (!group_layer) return QModelIndex{};

  const auto row = group_layer->indexOf(layer);
  Q_ASSERT(row >= 0);

  return createIndex(row, column, layer);
}

QModelIndex LayersTreeModel::index(int row, int column,
                                   const QModelIndex &parent) const {
  auto parent_layer = m_flow->getRootLayer();
  if (parent.isValid())
    parent_layer = static_cast<GroupLayer *>(parent.internalPointer());

  if (parent_layer->size() <= row) return QModelIndex{};
  return createIndex(row, column, parent_layer->at(row));
}

QModelIndex LayersTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex{};

  auto child_item = static_cast<Layer *>(index.internalPointer());
  return LayersTreeModel::index(child_item->getParent());
}

int LayersTreeModel::rowCount(const QModelIndex &parent) const {
  if (!m_document) return 0;

  if (!parent.isValid()) {
    auto root_layer = m_flow->getRootLayer();
    return static_cast<int>(root_layer->size());
  } else {
    auto layer = static_cast<Layer *>(parent.internalPointer());
    auto group_layer = static_cast<GroupLayer *>(layer);
    return group_layer->size();
  }
}

int LayersTreeModel::columnCount(const QModelIndex &parent) const { return 3; }

QStringList LayersTreeModel::mimeTypes() const {
  return QStringList{} << mimetype::Layers;
}

QMimeData *LayersTreeModel::mimeData(const QModelIndexList &indexes) const {
  if (indexes.isEmpty()) return nullptr;

  auto mime_data = new QMimeData;
  QByteArray encoded_data;
  QDataStream stream(&encoded_data, QDataStream::WriteOnly);

  auto layers = QList<Layer *>{};
  for (const auto &index : indexes) {
    auto layer = toLayer(index);
    if (layers.contains(layer)) continue;
    layers.append(layer);
  }

  auto hierarchical_ids = getLayersHierarchicalIds(layers);
  Q_ASSERT(!hierarchical_ids.empty());

  for (const auto &hierarchical_id : hierarchical_ids) {
    stream << hierarchical_id;
  }

  mime_data->setData(mimetype::Layers, encoded_data);
  return mime_data;
}

Qt::DropActions LayersTreeModel::supportedDropActions() const {
  return Qt::MoveAction;
}

bool LayersTreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                   int row, int column,
                                   const QModelIndex &parent) {
  if (!data || action != Qt::MoveAction) return false;
  if (!data->hasFormat(mimetype::Layers)) return false;

  auto parent_layer =
      parent.isValid() ? toLayer(parent) : m_flow->getRootLayer();
  if (parent_layer &&
      !parent_layer->isClassOrChild(GroupLayer::getStaticClassName()))
    return false;

  auto group_layer = static_cast<GroupLayer *>(parent_layer);

  const QByteArray encoded_data = data->data(QLatin1String(mimetype::Layers));
  QDataStream stream(encoded_data);
  QList<qsizetype> hierarchical_ids;

  while (!stream.atEnd()) {
    qsizetype hierarchical_id;
    stream >> hierarchical_id;
    hierarchical_ids.append(hierarchical_id);
  }

  auto index = std::max(0, row + 1);
  index = index > rowCount(parent) ? 0 : index;

  auto layers = getLayers(m_document, hierarchical_ids);
  m_document->getUndoStack()->push(
      new ReparentLayers(m_document, std::move(layers), group_layer, index));

  return true;
}

Layer *LayersTreeModel::toLayer(const QModelIndex &index) const {
  if (!index.isValid()) return nullptr;
  return static_cast<Layer *>(index.internalPointer());
}

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

QString LayersTreeModel::getName(const QModelIndex &index) const {
  auto layer = static_cast<Layer *>(index.internalPointer());
  return layer->getName();
}

QIcon LayersTreeModel::getIcon(const QModelIndex &index) const {
  auto layer = static_cast<Layer *>(index.internalPointer());

  if (layer->isClassOrChild(GroupLayer::getStaticClassName()))
    return QIcon(icons::x32::Group);
  if (layer->isClassOrChild(NodeLayer::getStaticClassName()))
    return QIcon(icons::x32::NodeLayer);

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

  m_document->getUndoStack()->push(
      new SetLayersName(m_document, {layer}, name));
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