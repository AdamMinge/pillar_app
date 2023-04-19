/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/event/objects_event.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

/* ----------------------------- ObjectChangedEvent ------------------------- */

ObjectsChangedEvent::ObjectsChangedEvent(Object *object, Type type)
    : ObjectsChangedEvent(QList<Object *>{object}, type) {}

ObjectsChangedEvent::ObjectsChangedEvent(const QList<Object *> &objects,
                                         Type type)
    : m_objects(objects), m_type(type) {}

ObjectsChangedEvent::~ObjectsChangedEvent() = default;

QList<Object *> ObjectsChangedEvent::getObjects() const { return m_objects; }

ObjectsChangedEvent::Type ObjectsChangedEvent::getType() const {
  return m_type;
}

bool ObjectsChangedEvent::contains(Object *object) const {
  return m_objects.contains(object);
}

/* ----------------------- ObjectsChangedPropertiesEvent -------------------- */

ObjectsChangedPropertiesEvent::ObjectsChangedPropertiesEvent(
    Object *object, Properties properties)
    : ObjectsChangedPropertiesEvent(QList<Object *>{object}, properties) {}

ObjectsChangedPropertiesEvent::ObjectsChangedPropertiesEvent(
    const QList<Object *> &objects, Properties properties)
    : ObjectsChangedEvent(objects, Type::ChangedProperties),
      m_properties(properties) {}

ObjectsChangedPropertiesEvent::~ObjectsChangedPropertiesEvent() = default;

ObjectsChangedPropertiesEvent::Properties
ObjectsChangedPropertiesEvent::getProperties() const {
  return m_properties;
}

/* -------------------------- ObjectsAddedRemovedEvent ---------------------- */

ObjectsAddedRemovedEvent::ObjectsAddedRemovedEvent(Object *object,
                                                   ObjectsType objects_type,
                                                   Type type)
    : ObjectsAddedRemovedEvent(QList<Object *>{object}, objects_type, type) {}

ObjectsAddedRemovedEvent::ObjectsAddedRemovedEvent(
    const QList<Object *> &objects, ObjectsType objects_type, Type type)
    : ObjectsChangedEvent(objects, type), m_objects_type(objects_type) {}

ObjectsAddedRemovedEvent::~ObjectsAddedRemovedEvent() = default;

ObjectsAddedRemovedEvent::ObjectsType ObjectsAddedRemovedEvent::getObjectsType()
    const {
  return m_objects_type;
}

/* ------------------------------ ObjectsAddedEvent ------------------------- */

ObjectsAddedEvent::ObjectsAddedEvent(Object *object, ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(object, objects_type, Type::Added) {}

ObjectsAddedEvent::ObjectsAddedEvent(const QList<Object *> &objects,
                                     ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(objects, objects_type, Type::Added) {}

ObjectsAddedEvent::~ObjectsAddedEvent() = default;

/* ------------------------------ ObjectsRemovedEvent -------------------------
 */

ObjectsRemovedEvent::ObjectsRemovedEvent(Object *object,
                                         ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(object, objects_type, Type::Removed) {}

ObjectsRemovedEvent::ObjectsRemovedEvent(const QList<Object *> &objects,
                                         ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(objects, objects_type, Type::Removed) {}

ObjectsRemovedEvent::~ObjectsRemovedEvent() = default;

}  // namespace plugin::flow_document