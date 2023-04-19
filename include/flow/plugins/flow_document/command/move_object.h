#ifndef FLOW_MOVE_OBJECT_H
#define FLOW_MOVE_OBJECT_H

/* ------------------------------------- Qt --------------------------------- */
#include <QGraphicsItem>
#include <QPointF>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

class Object;

class FlowDocument;

class FLOW_DOCUMENT_API MoveObject : public flow::Command {
 public:
  explicit MoveObject(FlowDocument *document, QList<Object *> objects,
                      const QPointF &move, flow::Command *parent = nullptr);
  ~MoveObject() override;

  void redo() override;
  void undo() override;

 private:
  void execute(const QPointF &move);

 private:
  FlowDocument *m_document;
  QList<Object *> m_objects;
  QPointF m_move;
};

}  // namespace plugin::flow_document

#endif  // FLOW_MOVE_OBJECT_H
