/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/factories/factories_view.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FactoriesView::FactoriesView(QWidget* parent)
    : utils::QtUnselectableTreeView(parent) {}

FactoriesView::~FactoriesView() = default;

}  // namespace flow_document