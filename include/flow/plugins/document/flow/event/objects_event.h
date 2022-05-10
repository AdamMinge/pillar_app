#ifndef FLOW_OBJECTS_EVENT_H
#define FLOW_OBJECTS_EVENT_H

/* ------------------------------------- Qt --------------------------------- */
#include <QFlag>
#include <QList>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow
{
  class Object;
}

class FLOW_DOCUMENT_API ObjectsChangedEvent
{
public:
  enum class Type
  {
    Added,
    Removed,
    ChangedProperties
  };

public:
  explicit ObjectsChangedEvent(flow::Object *object, Type type);
  explicit ObjectsChangedEvent(const QList<flow::Object *> &objects, Type type);
  virtual ~ObjectsChangedEvent();

  [[nodiscard]] QList<flow::Object *> getObjects() const;
  [[nodiscard]] Type getType() const;

  [[nodiscard]] bool contains(flow::Object *object) const;

private:
  QList<flow::Object *> m_objects;
  Type m_type;
};

class FLOW_DOCUMENT_API ObjectsChangedPropertiesEvent
    : public ObjectsChangedEvent
{
public:
  enum class Property
  {
    PositionProperty,
    CustomProperty
  };
  Q_DECLARE_FLAGS(Properties, Property)

public:
  explicit ObjectsChangedPropertiesEvent(
    flow::Object *object, Properties properties);
  explicit ObjectsChangedPropertiesEvent(
    const QList<flow::Object *> &objects, Properties properties);
  ~ObjectsChangedPropertiesEvent() override;

  [[nodiscard]] Properties getProperties() const;

private:
  QList<flow::Object *> m_objects;
  Properties m_properties;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ObjectsChangedPropertiesEvent::Properties)


class FLOW_DOCUMENT_API ObjectsAddedRemovedEvent : public ObjectsChangedEvent
{
public:
  enum class ObjectsType
  {
    Node
  };

public:
  ~ObjectsAddedRemovedEvent() override;

  [[nodiscard]] ObjectsType getObjectsType() const;

protected:
  explicit ObjectsAddedRemovedEvent(
    flow::Object *object, ObjectsType objects_type, Type type);
  explicit ObjectsAddedRemovedEvent(
    const QList<flow::Object *> &objects, ObjectsType objects_type, Type type);

private:
  QList<flow::Object *> m_objects;
  ObjectsType m_objects_type;
};

class FLOW_DOCUMENT_API ObjectsAddedEvent : public ObjectsAddedRemovedEvent
{
public:
  explicit ObjectsAddedEvent(flow::Object *object, ObjectsType objects_type);
  explicit ObjectsAddedEvent(
    const QList<flow::Object *> &objects, ObjectsType objects_type);
  ~ObjectsAddedEvent() override;
};

class FLOW_DOCUMENT_API ObjectsRemovedEvent : public ObjectsAddedRemovedEvent
{
public:
  explicit ObjectsRemovedEvent(flow::Object *object, ObjectsType objects_type);
  explicit ObjectsRemovedEvent(
    const QList<flow::Object *> &objects, ObjectsType objects_type);
  ~ObjectsRemovedEvent() override;
};


#endif//FLOW_OBJECTS_EVENT_H
