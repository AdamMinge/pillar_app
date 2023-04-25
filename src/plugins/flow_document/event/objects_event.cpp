/* ----------------------------------- Local -------------------------------- */
#include "flow_document/event/objects_event.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------- ObjectsChangedEvent -------------------------
 */

ObjectsChangedEvent::ObjectsChangedEvent(const QList<FlowObject *> &objects,
                                         Type type)
    : ChangeEvent(type), m_objects(objects) {}

ObjectsChangedEvent::~ObjectsChangedEvent() = default;

QList<FlowObject *> ObjectsChangedEvent::getObjects() const {
  return m_objects;
}

bool ObjectsChangedEvent::contains(FlowObject *object) const {
  return m_objects.contains(object);
}

/* ----------------------- ObjectsChangedPropertiesEvent ---------------------
 */

ObjectsChangedPropertiesEvent::ObjectsChangedPropertiesEvent(
    FlowObject *object, Properties properties)
    : ObjectsChangedPropertiesEvent(QList<FlowObject *>{object}, properties) {}

ObjectsChangedPropertiesEvent::ObjectsChangedPropertiesEvent(
    const QList<FlowObject *> &objects, Properties properties)
    : ObjectsChangedEvent(objects, Type::ObjectsChangedProperties),
      m_properties(properties) {}

ObjectsChangedPropertiesEvent::~ObjectsChangedPropertiesEvent() = default;

ObjectsChangedPropertiesEvent::Properties
ObjectsChangedPropertiesEvent::getProperties() const {
  return m_properties;
}

/* --------------------------- ObjectsAddedRemovedEvent ------------------------
 */

ObjectsAddedRemovedEvent::ObjectsAddedRemovedEvent(
    const QList<FlowObject *> &objects, ObjectsType objects_type, Type type)
    : ObjectsChangedEvent(objects, type), m_objects_type(objects_type) {}

ObjectsAddedRemovedEvent::~ObjectsAddedRemovedEvent() = default;

ObjectsAddedRemovedEvent::ObjectsType ObjectsAddedRemovedEvent::getObjectsType()
    const {
  return m_objects_type;
}

/* ------------------------------- ObjectsAddedEvent --------------------------
 */

ObjectsAddedEvent::ObjectsAddedEvent(FlowObject *object,
                                     ObjectsType objects_type)
    : ObjectsAddedRemovedEvent({object}, objects_type, Type::ObjectsAdded) {}

ObjectsAddedEvent::ObjectsAddedEvent(const QList<FlowObject *> &objects,
                                     ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(objects, objects_type, Type::ObjectsAdded) {}

ObjectsAddedEvent::~ObjectsAddedEvent() = default;

/* ------------------------------ ObjectsRemovedEvent ------------------------
 */

ObjectsRemovedEvent::ObjectsRemovedEvent(FlowObject *object,
                                         ObjectsType objects_type)
    : ObjectsAddedRemovedEvent({object}, objects_type, Type::ObjectsRemoved) {}

ObjectsRemovedEvent::ObjectsRemovedEvent(const QList<FlowObject *> &objects,
                                         ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(objects, objects_type, Type::ObjectsRemoved) {}

ObjectsRemovedEvent::~ObjectsRemovedEvent() = default;

}  // namespace flow_document