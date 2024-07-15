/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/factories/factories_view.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FactoriesView::FactoriesView(QWidget* parent)
    : qtils::QtUnselectableTreeView(parent) {
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setDragDropMode(QAbstractItemView::DragOnly);
}

FactoriesView::~FactoriesView() = default;

}  // namespace flow_document