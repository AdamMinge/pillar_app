/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/objects/objects_tree_model.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

ObjectsTreeModel::ObjectsTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_document(nullptr), m_flow(nullptr) {}

ObjectsTreeModel::~ObjectsTreeModel() = default;

void ObjectsTreeModel::setDocument(FlowDocument *flow_document) {
  if (m_document == flow_document) return;

  m_document = flow_document;
}

FlowDocument *ObjectsTreeModel::getDocument() const { return m_document; }

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