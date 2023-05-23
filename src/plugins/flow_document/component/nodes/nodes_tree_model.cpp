/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/nodes/nodes_tree_model.h"

#include "flow_document/event/change_event.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

NodesTreeModel::NodesTreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_document(nullptr), m_flow(nullptr) {}

NodesTreeModel::~NodesTreeModel() = default;

void NodesTreeModel::setDocument(FlowDocument *flow_document) {
  if (m_document == flow_document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::event, this,
               &NodesTreeModel::onEvent);
  }

  m_document = flow_document;

  if (m_document) {
    connect(m_document, &FlowDocument::event, this, &NodesTreeModel::onEvent);
  }

  m_flow = m_document ? m_document->getFlow() : nullptr;
}

FlowDocument *NodesTreeModel::getDocument() const { return m_document; }

Qt::ItemFlags NodesTreeModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}

QVariant NodesTreeModel::data(const QModelIndex &index, int role) const {
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

QVariant NodesTreeModel::headerData(int section, Qt::Orientation orientation,
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

QModelIndex NodesTreeModel::index(int row, int column,
                                  const QModelIndex &parent) const {
  return QModelIndex{};
}

QModelIndex NodesTreeModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) return QModelIndex{};

  return QModelIndex{};
}

int NodesTreeModel::rowCount(const QModelIndex &parent) const {
  if (!m_document) return 0;

  return 0;
}

int NodesTreeModel::columnCount(const QModelIndex &parent) const { return 1; }

void NodesTreeModel::onEvent(const ChangeEvent &event) {
  switch (event.getType()) { using enum ChangeEvent::Type; }
}

QString NodesTreeModel::getName(const QModelIndex &index) const {
  return QString{};
}

QIcon NodesTreeModel::getIcon(const QModelIndex &index) const {
  return QIcon{};
}

}  // namespace flow_document