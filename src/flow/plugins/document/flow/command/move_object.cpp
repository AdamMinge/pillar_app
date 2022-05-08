/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/command/move_object.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/object.h>
/* -------------------------------------------------------------------------- */

MoveObject::MoveObject(
  QList<flow::Object *> objects, const QPointF &move,
  flow::command::Command *parent)
    : flow::command::Command(QLatin1String("MoveObject"), parent),
      m_objects(std::move(objects)), m_move(move)
{
  setText(QObject::tr("Move Item"));
}

MoveObject::~MoveObject() = default;

void MoveObject::redo()
{
  for (auto object : m_objects)
    object->setPosition(object->getPosition() + m_move);
}

void MoveObject::undo()
{
  for (auto object : m_objects)
    object->setPosition(object->getPosition() - m_move);
}