/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/layers/layers_tree_model.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

LayersTreeModel::LayersTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_document(nullptr), m_flow(nullptr) {}

LayersTreeModel::~LayersTreeModel() = default;

void LayersTreeModel::setDocument(FlowDocument *flow_document) {
  if (m_document == flow_document) return;

  m_document = flow_document;
}

FlowDocument *LayersTreeModel::getDocument() const { return m_document; }

Qt::ItemFlags LayersTreeModel::flags(const QModelIndex &index) const {}

QVariant LayersTreeModel::data(const QModelIndex &index, int role) const {}

QVariant LayersTreeModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {}

QModelIndex LayersTreeModel::index(int row, int column,
                                   const QModelIndex &parent) const {}

QModelIndex LayersTreeModel::parent(const QModelIndex &index) const {}

int LayersTreeModel::rowCount(const QModelIndex &parent) const {}

int LayersTreeModel::columnCount(const QModelIndex &parent) const {}

}  // namespace flow_document