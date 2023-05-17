/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/layers/layers_view.h"

#include "flow_document/component/layers/layers_tree_model.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QHeaderView>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/delegate/icon_check_delegate.h>
#include <utils/dpi/dpi.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

LayersView::LayersView(QWidget* parent) : QTreeView(parent) {
  setHeaderHidden(true);
  setUniformRowHeights(true);
  setSelectionMode(QAbstractItemView::ExtendedSelection);

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

}  // namespace flow_document