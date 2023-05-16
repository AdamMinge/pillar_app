#ifndef FLOW_DOCUMENT_LAYERS_VIEW_H
#define FLOW_DOCUMENT_LAYERS_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API LayersView : public QTreeView {
  Q_OBJECT

 public:
  explicit LayersView(QWidget* parent = nullptr);
  ~LayersView() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYERS_VIEW_H
