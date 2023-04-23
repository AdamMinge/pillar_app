/* ----------------------------------- Local -------------------------------- */
#include "flow_document/event/objects_event.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------- ObjectsChangedEvent -------------------------
 */

ObjectsChangedEvent::ObjectsChangedEvent(const QList<Object *> &objects,
                                         Type type)
    : ChangeEvent(type), m_objects(objects) {}

ObjectsChangedEvent::~ObjectsChangedEvent() = default;

QList<Object *> ObjectsChangedEvent::getObjects() const { return m_objects; }

bool ObjectsChangedEvent::contains(Object *object) const {
  return m_objects.contains(object);
}

/* ----------------------- ObjectsChangedPropertiesEvent ---------------------
 */

ObjectsChangedPropertiesEvent::ObjectsChangedPropertiesEvent(
    Object *object, Properties properties)
    : ObjectsChangedPropertiesEvent(QList<Object *>{object}, properties) {}

ObjectsChangedPropertiesEvent::ObjectsChangedPropertiesEvent(
    const QList<Object *> &objects, Properties properties)
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
    const QList<Object *> &objects, ObjectsType objects_type, Type type)
    : ObjectsChangedEvent(objects, type), m_objects_type(objects_type) {}

ObjectsAddedRemovedEvent::~ObjectsAddedRemovedEvent() = default;

ObjectsAddedRemovedEvent::ObjectsType ObjectsAddedRemovedEvent::getObjectsType()
    const {
  return m_objects_type;
}

/* ------------------------------- ObjectsAddedEvent --------------------------
 */

ObjectsAddedEvent::ObjectsAddedEvent(Object *object, ObjectsType objects_type)
    : ObjectsAddedRemovedEvent({object}, objects_type, Type::ObjectsAdded) {}

ObjectsAddedEvent::ObjectsAddedEvent(const QList<Object *> &objects,
                                     ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(objects, objects_type, Type::ObjectsAdded) {}

ObjectsAddedEvent::~ObjectsAddedEvent() = default;

/* ------------------------------ ObjectsRemovedEvent ------------------------
 */

ObjectsRemovedEvent::ObjectsRemovedEvent(Object *object,
                                         ObjectsType objects_type)
    : ObjectsAddedRemovedEvent({object}, objects_type, Type::ObjectsRemoved) {}

ObjectsRemovedEvent::ObjectsRemovedEvent(const QList<Object *> &objects,
                                         ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(objects, objects_type, Type::ObjectsRemoved) {}

ObjectsRemovedEvent::~ObjectsRemovedEvent() = default;

}  // namespace flow_document