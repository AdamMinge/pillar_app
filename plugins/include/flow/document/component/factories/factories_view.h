#ifndef FLOW_DOCUMENT_FACTORIES_VIEW_H
#define FLOW_DOCUMENT_FACTORIES_VIEW_H

/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/view/unselectable_view.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_DOCUMENT_API FactoriesView
    : public qtils::QtUnselectableTreeView {
  Q_OBJECT

 public:
  explicit FactoriesView(QWidget* parent = nullptr);
  ~FactoriesView() override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_FACTORIES_VIEW_H
