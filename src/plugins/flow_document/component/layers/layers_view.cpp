/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/layers/layers_view.h"

#include "flow_document/component/layers/layers_tree_model.h"
#include "flow_document/flow_document.h"
#include "flow_document/flow_document_action_handler.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QContextMenuEvent>
#include <QHeaderView>
#include <QScopedValueRollback>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/delegate/conditional_bold_delegate.h>
#include <utils/delegate/icon_check_delegate.h>
#include <utils/dpi/dpi.h>
#include <utils/model/cast.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

LayersView::LayersView(QWidget *parent)
    : QTreeView(parent), m_document(nullptr), m_updating_selection(false) {
  setHeaderHidden(true);
  setUniformRowHeights(true);
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setDragDropMode(QAbstractItemView::InternalMove);

  setItemDelegateForColumn(
      LayersTreeModel::Column::NameColumn,
      new utils::QtConditionalBoldDelegate([this](const auto &index) {
        auto selection_model = this->selectionModel();
        Q_ASSERT(selection_model);
        auto current_index = selection_model->currentIndex();

        return index.parent() == current_index.parent() &&
               index.row() == current_index.row();
      }));
  setItemDelegateForColumn(
      LayersTreeModel::Column::VisibleColumn,
      new utils::QtIconCheckDelegate(QIcon(icons::x16::Visible),
                                     QIcon(icons::x16::Hidden), true, this));
  setItemDelegateForColumn(
      LayersTreeModel::Column::LockedColumn,
      new utils::QtIconCheckDelegate(QIcon(icons::x16::Locked),
                                     QIcon(icons::x16::Unlocked), true, this));

  header()->setStretchLastSection(false);
}

LayersView::~LayersView() = default;

void LayersView::setDocument(FlowDocument *document) {
  if (m_document == document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::currentLayerChanged, this,
               &LayersView::onCurrentLayerChanged);
    disconnect(m_document, &FlowDocument::selectedLayersChanged, this,
               &LayersView::onSelectedLayersChanged);
    disconnect(selectionModel(), &QItemSelectionModel::currentRowChanged, this,
               &LayersView::onCurrentRowChanged);
  }

  m_document = document;

  if (m_document) {
    connect(m_document, &FlowDocument::currentLayerChanged, this,
            &LayersView::onCurrentLayerChanged);
    connect(m_document, &FlowDocument::selectedLayersChanged, this,
            &LayersView::onSelectedLayersChanged);
    connect(selectionModel(), &QItemSelectionModel::currentRowChanged, this,
            &LayersView::onCurrentRowChanged);
  }
}

FlowDocument *LayersView::getDocument() const { return m_document; }

void LayersView::contextMenuEvent(QContextMenuEvent *event) {
  const auto &handler = FlowDocumentActionHandler::getInstance();

  QMenu menu;
  menu.addMenu(handler.createNewLayerMenu(&menu));
  menu.addAction(handler.getRemoveLayerAction());
  menu.addAction(handler.getRaiseLayerAction());
  menu.addAction(handler.getLowerLayerAction());
  menu.addAction(handler.getDuplicateLayerAction());
  menu.addSeparator();
  menu.addAction(handler.getShowHideOtherLayersAction());
  menu.addAction(handler.getLockUnlockOtherLayersAction());

  menu.exec(event->globalPos());
}

void LayersView::selectionChanged(const QItemSelection &selected,
                                  const QItemSelection &deselected) {
  QTreeView::selectionChanged(selected, deselected);

  if (!m_document) return;
  if (m_updating_selection) return;

  const auto indexes = selectionModel()->selectedRows();
  auto layers_model = utils::toSourceModel<LayersTreeModel>(model());
  Q_ASSERT(layers_model);

  auto layers = QList<Layer *>{};
  for (const auto &index : indexes) {
    auto source_index = utils::mapToSourceIndex(index, model());
    auto layer = layers_model->toLayer(source_index);
    Q_ASSERT(layer);

    layers.append(layer);
  }

  m_document->setSelectedLayers(layers);
}

QItemSelectionModel::SelectionFlags LayersView::selectionCommand(
    const QModelIndex &index, const QEvent *event) const {
  if (!index.isValid() && event && event->type() == QEvent::MouseButtonRelease)
    return QItemSelectionModel::NoUpdate;
  return QTreeView::selectionCommand(index, event);
}

void LayersView::onCurrentRowChanged(const QModelIndex &index) {
  if (!m_document) return;
  if (m_updating_selection) return;

  const auto source_index = utils::mapToSourceIndex(index, model());
  const auto layers_model = utils::toSourceModel<LayersTreeModel>(model());
  auto current_layer = layers_model->toLayer(source_index);

  m_document->setCurrentLayer(current_layer);
}

void LayersView::onCurrentLayerChanged(Layer *layer) {
  auto layers_model = utils::toSourceModel<LayersTreeModel>(model());
  const auto source_index = layer ? layers_model->index(layer) : QModelIndex{};
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

void LayersView::onSelectedLayersChanged(const QList<Layer *> &layers) {
  if (m_updating_selection) return;

  auto layers_model = utils::toSourceModel<LayersTreeModel>(model());
  const auto source_indexes = QList<QModelIndex>{};

  auto selection = QItemSelection{};
  for (auto layer : layers) {
    const auto source_index = layers_model->index(layer);
    const auto index = utils::mapFromSourceIndex(source_index, model());
    selection.select(index, index);
  }

  QScopedValueRollback<bool> updating(m_updating_selection, true);
  selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect |
                                          QItemSelectionModel::Rows);
}

}  // namespace flow_document