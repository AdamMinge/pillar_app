/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/nodes/nodes_view.h"

#include "flow_document/component/nodes/nodes_tree_model.h"
#include "flow_document/flow_document.h"
#include "flow_document/flow_document_action_handler.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QContextMenuEvent>
#include <QHeaderView>
#include <QScopedValueRollback>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/delegate/icon_check_delegate.h>
#include <utils/dpi/dpi.h>
#include <utils/model/cast.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

NodesView::NodesView(QWidget *parent)
    : QTreeView(parent), m_document(nullptr), m_updating_selection(false) {
  setHeaderHidden(true);
  setUniformRowHeights(true);
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setDragDropMode(QAbstractItemView::InternalMove);

  setItemDelegateForColumn(
      NodesTreeModel::Column::VisibleColumn,
      new utils::QtIconCheckDelegate(QIcon(icons::x16::Visible),
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
    disconnect(selectionModel(), &QItemSelectionModel::currentRowChanged, this,
               &NodesView::onCurrentRowChanged);
  }

  m_document = document;

  if (m_document) {
    connect(m_document, &FlowDocument::currentNodeChanged, this,
            &NodesView::onCurrentNodeChanged);
    connect(m_document, &FlowDocument::selectedNodesChanged, this,
            &NodesView::onSelectedNodesChanged);
    connect(selectionModel(), &QItemSelectionModel::currentRowChanged, this,
            &NodesView::onCurrentRowChanged);
  }

  onCurrentNodeChanged(m_document ? m_document->getCurrentNode() : nullptr);
  onSelectedNodesChanged(m_document ? m_document->getSelectedNodes()
                                    : QList<Node *>{});
}

FlowDocument *NodesView::getDocument() const { return m_document; }

void NodesView::contextMenuEvent(QContextMenuEvent *event) {
  const auto &handler = FlowDocumentActionHandler::getInstance();

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
  auto nodes_model = utils::toSourceModel<NodesTreeModel>(model());
  Q_ASSERT(nodes_model);

  auto nodes = QList<Node *>{};
  for (const auto &index : indexes) {
    auto source_index = utils::mapToSourceIndex(index, model());
    auto node = nodes_model->toNode(source_index);
    if (node) nodes.append(node);
  }

  m_document->setSelectedNodes(nodes);
}

QItemSelectionModel::SelectionFlags NodesView::selectionCommand(
    const QModelIndex &index, const QEvent *event) const {
  if (!index.isValid() && event && event->type() == QEvent::MouseButtonRelease)
    return QItemSelectionModel::NoUpdate;
  return QTreeView::selectionCommand(index, event);
}

void NodesView::onCurrentRowChanged(const QModelIndex &index) {
  if (!m_document) return;
  if (m_updating_selection) return;

  const auto source_index = utils::mapToSourceIndex(index, model());
  const auto nodes_model = utils::toSourceModel<NodesTreeModel>(model());

  if (auto current_node = nodes_model->toNode(source_index); current_node) {
    m_document->setCurrentNode(current_node);
  } else if (auto current_layer = nodes_model->toLayer(source_index);
             current_layer) {
    m_document->switchCurrentLayer(current_layer);
  }
}

void NodesView::onCurrentNodeChanged(Node *node) {
  auto nodes_model = utils::toSourceModel<NodesTreeModel>(model());
  const auto source_index = node ? nodes_model->index(node) : QModelIndex{};
  const auto index = utils::mapFromSourceIndex(source_index, model());
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

  auto nodes_model = utils::toSourceModel<NodesTreeModel>(model());
  const auto source_indexes = QList<QModelIndex>{};

  auto selection = QItemSelection{};
  for (auto node : nodes) {
    const auto source_index = nodes_model->index(node);
    const auto index = utils::mapFromSourceIndex(source_index, model());
    selection.select(index, index);
  }

  QScopedValueRollback<bool> updating(m_updating_selection, true);
  selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect |
                                          QItemSelectionModel::Rows);
}

void NodesView::onRowsInserted(const QModelIndex &parent, int first, int last) {
  const auto index =
      model()->index(last, NodesTreeModel::Column::NameColumn, parent);

  const auto nodes_model = utils::toSourceModel<NodesTreeModel>(model());
  const auto source_index = utils::mapToSourceIndex(index, model());
  auto node = nodes_model->toNode(source_index);

  m_document->switchCurrentNode(node);
}

}  // namespace flow_document