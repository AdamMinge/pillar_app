/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/factories/factories_view.h"
/* -------------------------------------------------------------------------- */

namespace flow {

FactoriesView::FactoriesView(QWidget* parent)
    : qtils::QtUnselectableTreeView(parent) {
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setDragDropMode(QAbstractItemView::DragOnly);
}

FactoriesView::~FactoriesView() = default;

}  // namespace flow