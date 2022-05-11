#ifndef FLOW_MOVE_OBJECT_H
#define FLOW_MOVE_OBJECT_H

/* ------------------------------------- Qt --------------------------------- */
#include <QGraphicsItem>
#include <QPointF>
/* ---------------------------------- LibFlow ------------------------------- */
#include "flow/libflow/command/command.h"
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow
{
  class Object;
}

class FlowDocument;

class FLOW_DOCUMENT_API MoveObject : public flow::command::Command
{
public:
  explicit MoveObject(
    FlowDocument *document, QList<flow::Object *> objects, const QPointF &move,
    flow::command::Command *parent = nullptr);
  ~MoveObject() override;

  void redo() override;
  void undo() override;

private:
  void execute(const QPointF &move);

private:
  FlowDocument *m_document;
  QList<flow::Object *> m_objects;
  QPointF m_move;
};

#endif//FLOW_MOVE_OBJECT_H
