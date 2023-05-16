#ifndef FLOW_DOCUMENT_OBJECTS_VIEW_H
#define FLOW_DOCUMENT_OBJECTS_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API ObjectsView : public QTreeView {
  Q_OBJECT

 public:
  explicit ObjectsView(QWidget* parent = nullptr);
  ~ObjectsView() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECTS_VIEW_H
