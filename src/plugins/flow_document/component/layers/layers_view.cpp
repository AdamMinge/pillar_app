/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/layers/layers_view.h"

#include "flow_document/component/layers/layers_tree_model.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QHeaderView>
/* ----------------------------------- Utils -------------------------------- */
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

}  // namespace flow_document