#ifndef FLOW_DOCUMENT_FACTORIES_VIEW_H
#define FLOW_DOCUMENT_FACTORIES_VIEW_H

/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/view/unselectable_view.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API FactoriesView : public qtils::QtUnselectableTreeView {
  Q_OBJECT

 public:
  explicit FactoriesView(QWidget* parent = nullptr);
  ~FactoriesView() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FACTORIES_VIEW_H
