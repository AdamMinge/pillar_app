/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/move_object.h"

#include "flow_document/event/objects_event.h"
#include "flow_document/flow/flow_object.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

MoveObject::MoveObject(FlowDocument *document, QList<FlowObject *> objects,
                       const QPointF &move, egnite::Command *parent)
    : egnite::Command(QLatin1String("MoveObject"), parent),
      m_document(document),
      m_objects(std::move(objects)),
      m_move(move) {
  setText(QObject::tr("Move Item"));
}

MoveObject::~MoveObject() = default;

void MoveObject::redo() { execute(m_move); }

void MoveObject::undo() { execute(-m_move); }

void MoveObject::execute(const QPointF &move) {
  for (auto object : m_objects)
    object->setPosition(object->getPosition() + move);

  Q_EMIT m_document->event(ObjectsChangedPropertiesEvent(
      m_objects, ObjectsChangedPropertiesEvent::Property::PositionProperty));
}

}  // namespace flow_document
