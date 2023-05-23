/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/layers/layers_view.h"

#include "flow_document/component/layers/layers_tree_model.h"
#include "flow_document/flow_document.h"
#include "flow_document/flow_document_action_handler.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QContextMenuEvent>
#include <QHeaderView>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/delegate/conditional_bold_delegate.h>
#include <utils/delegate/icon_check_delegate.h>
#include <utils/dpi/dpi.h>
#include <utils/model/cast.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

LayersView::LayersView(QWidget *parent)
    : QTreeView(parent), m_document(nullptr) {
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
        return index == current_index;
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
    disconnect(selectionModel(), &QItemSelectionModel::selectionChanged, this,
               &LayersView::selectionChanged);
  }

  m_document = document;

  if (m_document) {
    connect(selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &LayersView::selectionChanged);
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

void LayersView::selectionChanged() {
  const auto indexes = selectionModel()->selectedRows();
  auto layers_model = utils::cast<LayersTreeModel>(model());
  Q_ASSERT(layers_model);

  auto layers = QList<Layer *>{};
  for (const auto &index : indexes) {
    auto source_index = utils::mapToSourceIndex(index, model());
    auto layer = layers_model->toLayer(source_index);
    Q_ASSERT(layer);

    layers.append(layer);
  }

  Q_ASSERT(m_document);
  m_document->setSelectedLayers(layers);
}

QItemSelectionModel::SelectionFlags LayersView::selectionCommand(
    const QModelIndex &index, const QEvent *event) const {
  if (!index.isValid() && event && event->type() == QEvent::MouseButtonRelease)
    return QItemSelectionModel::NoUpdate;
  return QTreeView::selectionCommand(index, event);
}

}  // namespace flow_document