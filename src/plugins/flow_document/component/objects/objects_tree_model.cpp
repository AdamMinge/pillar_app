/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/objects/objects_tree_model.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

ObjectsTreeModel::ObjectsTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_flow_document(nullptr), m_flow(nullptr) {}

ObjectsTreeModel::~ObjectsTreeModel() = default;

void ObjectsTreeModel::setDocument(FlowDocument *flow_document) {
  if (m_flow_document == flow_document) return;

  if (m_flow_document) {
    // TODO
  }

  m_flow_document = flow_document;

  if (m_flow_document) {
    // TODO
  }
}

FlowDocument *ObjectsTreeModel::getDocument() const { return m_flow_document; }

Qt::ItemFlags ObjectsTreeModel::flags(const QModelIndex &index) const {}

QVariant ObjectsTreeModel::data(const QModelIndex &index, int role) const {}

QVariant ObjectsTreeModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {}

QModelIndex ObjectsTreeModel::index(int row, int column,
                                    const QModelIndex &parent) const {}

QModelIndex ObjectsTreeModel::parent(const QModelIndex &index) const {}

int ObjectsTreeModel::rowCount(const QModelIndex &parent) const {}

int ObjectsTreeModel::columnCount(const QModelIndex &parent) const {}

}  // namespace flow_document