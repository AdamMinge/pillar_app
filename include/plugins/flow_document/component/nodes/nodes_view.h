#ifndef FLOW_DOCUMENT_NODES_VIEW_H
#define FLOW_DOCUMENT_NODES_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API NodesView : public QTreeView {
  Q_OBJECT

 public:
  explicit NodesView(QWidget* parent = nullptr);
  ~NodesView() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODES_VIEW_H
