/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/layers/layers_tree_model.h"

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

  m_document = flow_document;

  if (m_document) {
    connect(m_document, &FlowDocument::event, this, &LayersTreeModel::onEvent);
  }

  m_flow = m_document ? m_document->getFlow() : nullptr;
}

FlowDocument *LayersTreeModel::getDocument() const { return m_document; }

Qt::ItemFlags LayersTreeModel::flags(const QModelIndex &index) const {
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}

QVariant LayersTreeModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return QVariant{};

  switch (role) {
    case Qt::DisplayRole:
    case Role::NameRole:
      return getName(index);

    case Qt::DecorationRole:
    case Role::IconRole:
      return getIcon(index);

    default:
      return QVariant{};
  }
}

QVariant LayersTreeModel::headerData(int section, Qt::Orientation orientation,
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

QModelIndex LayersTreeModel::index(int row, int column,
                                   const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) return QModelIndex{};

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
    if (layer->getType() == Layer::Type::GroupLayer) {
      auto group_layer = static_cast<GroupLayer *>(layer);
      return group_layer->size();
    }

    return 0;
  }
}

int LayersTreeModel::columnCount(const QModelIndex &parent) const { return 1; }

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
  }
}

QModelIndex LayersTreeModel::index(Layer *layer) const {
  Q_ASSERT(layer);
  const auto group_layer = layer->getParent();
  if (!group_layer) return QModelIndex{};

  const auto row = group_layer->indexOf(layer);
  Q_ASSERT(row >= 0);

  return createIndex(row, 0, layer);
}

QString LayersTreeModel::getName(const QModelIndex &index) const {
  auto layer = static_cast<Layer *>(index.internalPointer());
  return layer->getName();
}

QIcon LayersTreeModel::getIcon(const QModelIndex &index) const {
  auto layer = static_cast<Layer *>(index.internalPointer());
  switch (layer->getType()) {
    case Layer::Type::GroupLayer:
      return QIcon(icons::x32::GroupLayer);

    case Layer::Type::NodeLayer:
      return QIcon(icons::x32::NodeLayer);
  }

  return QIcon{};
}

}  // namespace flow_document