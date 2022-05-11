/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/command/move_object.h"
#include "flow/plugins/document/flow/event/objects_event.h"
#include "flow/plugins/document/flow/flow_document.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/object.h>
/* -------------------------------------------------------------------------- */

MoveObject::MoveObject(
  FlowDocument *document, QList<flow::Object *> objects, const QPointF &move,
  flow::command::Command *parent)
    : flow::command::Command(QLatin1String("MoveObject"), parent),
      m_document(document), m_objects(std::move(objects)), m_move(move)
{
  setText(QObject::tr("Move Item"));
}

MoveObject::~MoveObject() = default;

void MoveObject::redo() { execute(m_move); }

void MoveObject::undo() { execute(-m_move); }

void MoveObject::execute(const QPointF &move)
{
  for (auto object : m_objects)
    object->setPosition(object->getPosition() + move);

  Q_EMIT m_document->event(ObjectsChangedPropertiesEvent(
    m_objects, ObjectsChangedPropertiesEvent::Property::PositionProperty));
}
