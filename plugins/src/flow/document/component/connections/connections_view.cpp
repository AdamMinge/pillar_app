/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/connections/connections_view.h"

#include "flow/document/action_handler.h"
#include "flow/document/component/connections/connections_tree_model.h"
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

ConnectionsView::ConnectionsView(QWidget *parent)
    : QTreeView(parent), m_document(nullptr), m_updating_selection(false) {
  setHeaderHidden(true);
  setUniformRowHeights(true);
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setDragDropMode(QAbstractItemView::InternalMove);

  setItemDelegateForColumn(
      ConnectionsTreeModel::Column::VisibleColumn,
      new qtils::QtIconCheckDelegate(QIcon(icons::x16::Visible),
                                     QIcon(icons::x16::Hidden), true, this));

  header()->setStretchLastSection(false);
}

ConnectionsView::~ConnectionsView() = default;

void ConnectionsView::setDocument(FlowDocument *document) {
  if (m_document == document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::currentConnectionChanged, this,
               &ConnectionsView::onCurrentConnectionChanged);
    disconnect(m_document, &FlowDocument::selectedConnectionsChanged, this,
               &ConnectionsView::onSelectedConnectionsChanged);
  }

  m_document = document;

  if (m_document) {
    connect(m_document, &FlowDocument::currentConnectionChanged, this,
            &ConnectionsView::onCurrentConnectionChanged);
    connect(m_document, &FlowDocument::selectedConnectionsChanged, this,
            &ConnectionsView::onSelectedConnectionsChanged);
  }

  onCurrentConnectionChanged(m_document ? m_document->getCurrentConnection()
                                        : nullptr);
  onSelectedConnectionsChanged(m_document ? m_document->getSelectedConnections()
                                          : QList<Connection *>{});
}

FlowDocument *ConnectionsView::getDocument() const { return m_document; }

void ConnectionsView::setModel(QAbstractItemModel *model) {
  if (auto current_model = QTreeView::model()) {
    disconnect(current_model, &QAbstractItemModel::rowsInserted, this,
               &ConnectionsView::onRowsInserted);
    disconnect(current_model, &QAbstractItemModel::rowsAboutToBeRemoved, this,
               &ConnectionsView::onRowsRemoved);
  }

  QTreeView::setModel(model);

  if (auto current_model = QTreeView::model()) {
    connect(current_model, &QAbstractItemModel::rowsInserted, this,
            &ConnectionsView::onRowsInserted);
    connect(current_model, &QAbstractItemModel::rowsAboutToBeRemoved, this,
            &ConnectionsView::onRowsRemoved);
  }
}

void ConnectionsView::contextMenuEvent(QContextMenuEvent *event) {
  const auto &handler = ActionHandler::getInstance();

  QMenu menu;
  menu.addAction(handler.getAddConnectionAction());
  menu.addAction(handler.getRemoveConnectionAction());

  menu.exec(event->globalPos());
}

void ConnectionsView::selectionChanged(const QItemSelection &selected,
                                       const QItemSelection &deselected) {
  QTreeView::selectionChanged(selected, deselected);

  if (!m_document) return;
  if (m_updating_selection) return;

  const auto indexes = selectionModel()->selectedRows();
  auto connections_model = qtils::toSourceModel<ConnectionsTreeModel>(model());
  Q_ASSERT(connections_model);

  auto connections = QList<Connection *>{};
  for (const auto &index : indexes) {
    auto source_index = qtils::mapToSourceIndex(index, model());
    auto connection = connections_model->toConnection(source_index);
    if (connection) connections.append(connection);
  }

  QScopedValueRollback<bool> updating(m_updating_selection, true);
  m_document->setSelectedConnections(connections);
}

void ConnectionsView::mousePressEvent(QMouseEvent *event) {
  QTreeView::mousePressEvent(event);
  if (!m_document) return;

  const auto index = indexAt(event->pos());
  const auto source_index = qtils::mapToSourceIndex(index, model());
  const auto connections_model =
      qtils::toSourceModel<ConnectionsTreeModel>(model());

  if (auto current_connection = connections_model->toConnection(source_index);
      current_connection) {
    m_document->setCurrentObject(current_connection);
    m_document->setCurrentConnection(current_connection);
  } else if (auto current_layer = connections_model->toLayer(source_index);
             current_layer) {
    m_document->setCurrentObject(current_layer);
    m_document->switchSelectedLayers({current_layer});
  }
}

QItemSelectionModel::SelectionFlags ConnectionsView::selectionCommand(
    const QModelIndex &index, const QEvent *event) const {
  if (!index.isValid() && event && event->type() == QEvent::MouseButtonRelease)
    return QItemSelectionModel::NoUpdate;
  return QTreeView::selectionCommand(index, event);
}

void ConnectionsView::onCurrentConnectionChanged(Connection *connection) {
  auto connections_model = qtils::toSourceModel<ConnectionsTreeModel>(model());
  const auto source_index =
      connection ? connections_model->index(connection) : QModelIndex{};
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

void ConnectionsView::onSelectedConnectionsChanged(
    const QList<Connection *> &connections) {
  if (m_updating_selection) return;

  auto connections_model = qtils::toSourceModel<ConnectionsTreeModel>(model());
  const auto source_indexes = QList<QModelIndex>{};

  auto selection = QItemSelection{};
  for (auto connection : connections) {
    const auto source_index = connections_model->index(connection);
    const auto index = qtils::mapFromSourceIndex(source_index, model());
    selection.select(index, index);
  }

  QScopedValueRollback<bool> updating(m_updating_selection, true);
  selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect |
                                          QItemSelectionModel::Rows);
}

void ConnectionsView::onRowsInserted(const QModelIndex &parent, int first,
                                     int last) {
  const auto index =
      model()->index(last, ConnectionsTreeModel::Column::NameColumn, parent);

  const auto connections_model =
      qtils::toSourceModel<ConnectionsTreeModel>(model());
  const auto source_index = qtils::mapToSourceIndex(index, model());
  auto connection = connections_model->toConnection(source_index);

  if (connection) {
    m_document->setCurrentObject(connection);
    m_document->switchCurrentConnection(connection);
  }
}

void ConnectionsView::onRowsRemoved(const QModelIndex &parent, int first,
                                    int last) {
  const auto index =
      model()->index(last, ConnectionsTreeModel::Column::NameColumn, parent);
  const auto connections_model =
      qtils::toSourceModel<ConnectionsTreeModel>(model());
  const auto source_index = qtils::mapToSourceIndex(index, model());
  auto connection = connections_model->toConnection(source_index);

  if (connection) {
    const auto &selected_connections = m_document->getSelectedConnections();
    const auto current_connection = m_document->getCurrentConnection();

    if (selected_connections.empty() && current_connection) {
      m_document->setSelectedConnections({current_connection});
    }

    if (connection == current_connection) {
      m_document->setCurrentConnection(nullptr);
    }
  }
}

QModelIndex ConnectionsView::indexAt(const QPoint &position) const {
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