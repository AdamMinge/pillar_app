#ifndef FLOW_DOCUMENT_MOVE_OBJECT_H
#define FLOW_DOCUMENT_MOVE_OBJECT_H

/* ------------------------------------- Qt --------------------------------- */
#include <QGraphicsItem>
#include <QPointF>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowObject;

class FlowDocument;

class FLOW_DOCUMENT_API MoveObject : public egnite::Command {
 public:
  explicit MoveObject(FlowDocument *document, QList<FlowObject *> objects,
                      const QPointF &move, egnite::Command *parent = nullptr);
  ~MoveObject() override;

  void redo() override;
  void undo() override;

 private:
  void execute(const QPointF &move);

 private:
  FlowDocument *m_document;
  QList<FlowObject *> m_objects;
  QPointF m_move;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_MOVE_OBJECT_H
