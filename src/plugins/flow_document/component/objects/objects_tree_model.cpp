/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/objects/objects_tree_model.h"

#include "flow_document/event/change_event.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

ObjectsTreeModel::ObjectsTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_document(nullptr), m_flow(nullptr) {}

ObjectsTreeModel::~ObjectsTreeModel() = default;

void ObjectsTreeModel::setDocument(FlowDocument *flow_document) {
  if (m_document == flow_document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::event, this,
               &ObjectsTreeModel::onEvent);
  }

  m_document = flow_document;

  if (m_document) {
    connect(m_document, &FlowDocument::event, this, &ObjectsTreeModel::onEvent);
  }

  m_flow = m_document ? m_document->getFlow() : nullptr;
}

FlowDocument *ObjectsTreeModel::getDocument() const { return m_document; }

Qt::ItemFlags ObjectsTreeModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}

QVariant ObjectsTreeModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant{};

  switch (role) {
    case Qt::DisplayRole: {
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

QVariant ObjectsTreeModel::headerData(int section, Qt::Orientation orientation,
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

QModelIndex ObjectsTreeModel::index(int row, int column,
                                    const QModelIndex &parent) const {
  return QModelIndex{};
}

QModelIndex ObjectsTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex{};

  return QModelIndex{};
}

int ObjectsTreeModel::rowCount(const QModelIndex &parent) const {
  if (!m_document) return 0;

  return 0;
}

int ObjectsTreeModel::columnCount(const QModelIndex &parent) const { return 1; }

void ObjectsTreeModel::onEvent(const ChangeEvent &event) {
  switch (event.getType()) { using enum ChangeEvent::Type; }
}

QString ObjectsTreeModel::getName(const QModelIndex &index) const {
  return QString{};
}

QIcon ObjectsTreeModel::getIcon(const QModelIndex &index) const {
  return QIcon{};
}

}  // namespace flow_document