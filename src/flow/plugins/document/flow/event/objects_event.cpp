/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/event/objects_event.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- ObjectChangedEvent ------------------------- */

ObjectsChangedEvent::ObjectsChangedEvent(flow::Object *object, Type type)
    : ObjectsChangedEvent(QList<flow::Object *>{object}, type)
{}

ObjectsChangedEvent::ObjectsChangedEvent(
  const QList<flow::Object *> &objects, Type type)
    : m_objects(objects), m_type(type)
{}

ObjectsChangedEvent::~ObjectsChangedEvent() = default;

QList<flow::Object *> ObjectsChangedEvent::getObjects() const
{
  return m_objects;
}

ObjectsChangedEvent::Type ObjectsChangedEvent::getType() const
{
  return m_type;
}

bool ObjectsChangedEvent::contains(flow::Object *object) const
{
  return m_objects.contains(object);
}

/* ----------------------- ObjectsChangedPropertiesEvent -------------------- */

ObjectsChangedPropertiesEvent::ObjectsChangedPropertiesEvent(
  flow::Object *object, Properties properties)
    : ObjectsChangedPropertiesEvent(QList<flow::Object *>{object}, properties)
{}

ObjectsChangedPropertiesEvent::ObjectsChangedPropertiesEvent(
  const QList<flow::Object *> &objects, Properties properties)
    : ObjectsChangedEvent(objects, Type::ChangedProperties),
      m_properties(properties)
{}

ObjectsChangedPropertiesEvent::~ObjectsChangedPropertiesEvent() = default;

ObjectsChangedPropertiesEvent::Properties
ObjectsChangedPropertiesEvent::getProperties() const
{
  return m_properties;
}

/* -------------------------- ObjectsAddedRemovedEvent ---------------------- */

ObjectsAddedRemovedEvent::ObjectsAddedRemovedEvent(
  flow::Object *object, ObjectsType objects_type, Type type)
    : ObjectsAddedRemovedEvent(
        QList<flow::Object *>{object}, objects_type, type)
{}

ObjectsAddedRemovedEvent::ObjectsAddedRemovedEvent(
  const QList<flow::Object *> &objects, ObjectsType objects_type, Type type)
    : ObjectsChangedEvent(objects, type), m_objects_type(objects_type)
{}

ObjectsAddedRemovedEvent::~ObjectsAddedRemovedEvent() = default;

ObjectsAddedRemovedEvent::ObjectsType
ObjectsAddedRemovedEvent::getObjectsType() const
{
  return m_objects_type;
}

/* ------------------------------ ObjectsAddedEvent ------------------------- */

ObjectsAddedEvent::ObjectsAddedEvent(
  flow::Object *object, ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(object, objects_type, Type::Added)
{}

ObjectsAddedEvent::ObjectsAddedEvent(
  const QList<flow::Object *> &objects, ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(objects, objects_type, Type::Added)
{}

ObjectsAddedEvent::~ObjectsAddedEvent() = default;

/* ------------------------------ ObjectsRemovedEvent ------------------------- */

ObjectsRemovedEvent::ObjectsRemovedEvent(
  flow::Object *object, ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(object, objects_type, Type::Removed)
{}

ObjectsRemovedEvent::ObjectsRemovedEvent(
  const QList<flow::Object *> &objects, ObjectsType objects_type)
    : ObjectsAddedRemovedEvent(objects, objects_type, Type::Removed)
{}

ObjectsRemovedEvent::~ObjectsRemovedEvent() = default;
