/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/nodes/nodes_view.h"

#include "flow/document/action_handler.h"
#include "flow/document/component/nodes/nodes_tree_model.h"
#include "flow/document/document.h"
#include "flow/document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QContextMenuEvent>
#include <QHeaderView>
#include <QScopedValueRollback>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/delegate/icon_check_delegate.h>
#include <qtils/dpi/dpi.h>
#include <qtils/model/cast.h>
/* -------------------------------------------------------------------------- */

namespace flow {

NodesView::NodesView(QWidget *parent)
    : QTreeView(parent), m_document(nullptr), m_updating_selection(false) {
  setMouseTracking(true);
  setHeaderHidden(true);
  setUniformRowHeights(true);
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setDragDropMode(QAbstractItemView::InternalMove);

  setItemDelegateForColumn(
      NodesTreeModel::Column::VisibleColumn,
      new qtils::QtIconCheckDelegate(QIcon(icons::x16::Visible),
                                     QIcon(icons::x16::Hidden), true, this));

  header()->setStretchLastSection(false);
}

NodesView::~NodesView() = default;

void NodesView::setDocument(FlowDocument *document) {
  if (m_document == document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::currentNodeChanged, this,
               &NodesView::onCurrentNodeChanged);
    disconnect(m_document, &FlowDocument::selectedNodesChanged, this,
               &NodesView::onSelectedNodesChanged);
  }

  m_document = document;

  if (m_document) {
    connect(m_document, &FlowDocument::currentNodeChanged, this,
            &NodesView::onCurrentNodeChanged);
    connect(m_document, &FlowDocument::selectedNodesChanged, this,
            &NodesView::onSelectedNodesChanged);
  }

  onCurrentNodeChanged(m_document ? m_document->getCurrentNode() : nullptr);
  onSelectedNodesChanged(m_document ? m_document->getSelectedNodes()
                                    : QList<Node *>{});
}

FlowDocument *NodesView::getDocument() const { return m_document; }

void NodesView::setModel(QAbstractItemModel *model) {
  if (auto current_model = QTreeView::model()) {
    disconnect(current_model, &QAbstractItemModel::rowsInserted, this,
               &NodesView::onRowsInserted);
    disconnect(current_model, &QAbstractItemModel::rowsAboutToBeRemoved, this,
               &NodesView::onRowsRemoved);
  }

  QTreeView::setModel(model);

  if (auto current_model = QTreeView::model()) {
    connect(current_model, &QAbstractItemModel::rowsInserted, this,
            &NodesView::onRowsInserted);
    connect(current_model, &QAbstractItemModel::rowsAboutToBeRemoved, this,
            &NodesView::onRowsRemoved);
  }
}

void NodesView::contextMenuEvent(QContextMenuEvent *event) {
  const auto &handler = ActionHandler::getInstance();

  QMenu menu;
  menu.addMenu(handler.getAddNodeMenu());
  menu.addAction(handler.getRemoveNodeAction());
  menu.addAction(handler.getRaiseNodeAction());
  menu.addAction(handler.getLowerNodeAction());
  menu.addAction(handler.getDuplicateNodeAction());

  menu.exec(event->globalPos());
}

void NodesView::selectionChanged(const QItemSelection &selected,
                                 const QItemSelection &deselected) {
  QTreeView::selectionChanged(selected, deselected);

  if (!m_document) return;
  if (m_updating_selection) return;

  const auto indexes = selectionModel()->selectedRows();
  auto nodes_model = qtils::toSourceModel<NodesTreeModel>(model());
  Q_ASSERT(nodes_model);

  auto nodes = QList<Node *>{};
  for (const auto &index : indexes) {
    auto source_index = qtils::mapToSourceIndex(index, model());
    auto node = nodes_model->toNode(source_index);
    if (node) nodes.append(node);
  }

  QScopedValueRollback<bool> updating(m_updating_selection, true);
  m_document->setSelectedNodes(nodes);
}

QItemSelectionModel::SelectionFlags NodesView::selectionCommand(
    const QModelIndex &index, const QEvent *event) const {
  if (!index.isValid() && event && event->type() == QEvent::MouseButtonRelease)
    return QItemSelectionModel::NoUpdate;
  return QTreeView::selectionCommand(index, event);
}

void NodesView::mouseMoveEvent(QMouseEvent *event) {
  QTreeView::mouseMoveEvent(event);
  if (!m_document) return;

  const auto index = indexAt(event->pos());
  const auto nodes_model = qtils::toSourceModel<NodesTreeModel>(model());
  const auto source_index = qtils::mapToSourceIndex(index, model());
  auto node = nodes_model->toNode(source_index);

  auto hovered = QList<Node *>{};
  if (node) hovered.append(node);

  m_document->setHoveredNodes(hovered);
}

void NodesView::mousePressEvent(QMouseEvent *event) {
  QTreeView::mousePressEvent(event);
  if (!m_document) return;

  const auto index = indexAt(event->pos());
  const auto nodes_model = qtils::toSourceModel<NodesTreeModel>(model());
  const auto source_index = qtils::mapToSourceIndex(index, model());

  if (auto current_node = nodes_model->toNode(source_index); current_node) {
    m_document->setCurrentObject(current_node);
    m_document->setCurrentNode(current_node);
  } else if (auto current_layer = nodes_model->toLayer(source_index);
             current_layer) {
    m_document->setCurrentObject(current_layer);
    m_document->switchSelectedLayers({current_layer});
  }
}

bool NodesView::viewportEvent(QEvent *event) {
  if (event->type() == QEvent::Leave) {
    if (m_document) m_document->setHoveredNodes({});
  }

  return QTreeView::viewportEvent(event);
}

void NodesView::onCurrentNodeChanged(Node *node) {
  auto nodes_model = qtils::toSourceModel<NodesTreeModel>(model());
  const auto source_index = node ? nodes_model->index(node) : QModelIndex{};
  const auto index = qtils::mapFromSourceIndex(source_index, model());
  const auto current_index = currentIndex();

  if (current_index.parent() != index.parent() ||
      current_index.row() != index.row()) {
    QScopedValueRollback<bool> updating(m_updating_selection, true);
    selectionModel()->setCurrentIndex(index,
                                      QItemSelectionModel::ClearAndSelect |
                                          QItemSelectionModel::SelectCurrent |
                                          QItemSelectionModel::Rows);
  }
}

void NodesView::onSelectedNodesChanged(const QList<Node *> &nodes) {
  if (m_updating_selection) return;

  auto nodes_model = qtils::toSourceModel<NodesTreeModel>(model());
  const auto source_indexes = QList<QModelIndex>{};

  auto selection = QItemSelection{};
  for (auto node : nodes) {
    const auto source_index = nodes_model->index(node);
    const auto index = qtils::mapFromSourceIndex(source_index, model());
    selection.select(index, index);
  }

  QScopedValueRollback<bool> updating(m_updating_selection, true);
  selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect |
                                          QItemSelectionModel::Rows);
}

void NodesView::onRowsInserted(const QModelIndex &parent, int first, int last) {
  const auto index =
      model()->index(last, NodesTreeModel::Column::NameColumn, parent);

  const auto nodes_model = qtils::toSourceModel<NodesTreeModel>(model());
  const auto source_index = qtils::mapToSourceIndex(index, model());
  auto node = nodes_model->toNode(source_index);

  if (node) {
    m_document->setCurrentObject(node);
    m_document->switchCurrentNode(node);
  }
}

void NodesView::onRowsRemoved(const QModelIndex &parent, int first, int last) {
  const auto index =
      model()->index(last, NodesTreeModel::Column::NameColumn, parent);
  const auto nodes_model = qtils::toSourceModel<NodesTreeModel>(model());
  const auto source_index = qtils::mapToSourceIndex(index, model());
  auto node = nodes_model->toNode(source_index);

  if (node) {
    const auto &selected_nodes = m_document->getSelectedNodes();
    const auto current_node = m_document->getCurrentNode();

    if (selected_nodes.empty() && current_node) {
      m_document->setSelectedNodes({current_node});
    }

    if (node == current_node) {
      m_document->setCurrentNode(nullptr);
    }
  }
}

QModelIndex NodesView::indexAt(const QPoint &position) const {
  auto index = QTreeView::indexAt(position);
  if (index.isValid()) {
    auto expandIconRect = visualRect(index).adjusted(0, 0, indentation(), 0);
    if (!expandIconRect.contains(position)) {
      index = QModelIndex{};
    }
  }

  return index;
}

}  // namespace flow