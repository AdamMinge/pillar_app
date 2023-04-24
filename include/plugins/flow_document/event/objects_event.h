#ifndef FLOW_DOCUMENT_OBJECTS_EVENT_H
#define FLOW_DOCUMENT_OBJECTS_EVENT_H

/* ------------------------------------- Qt --------------------------------- */
#include <QFlag>
#include <QList>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/event/change_event.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Object;

class FLOW_DOCUMENT_API ObjectsChangedEvent : public ChangeEvent {
 public:
  explicit ObjectsChangedEvent(const QList<Object *> &objects, Type type);
  virtual ~ObjectsChangedEvent();

  [[nodiscard]] QList<Object *> getObjects() const;
  [[nodiscard]] bool contains(Object *object) const;

 private:
  QList<Object *> m_objects;
};

class FLOW_DOCUMENT_API ObjectsChangedPropertiesEvent
    : public ObjectsChangedEvent {
 public:
  enum class Property { PositionProperty, CustomProperty };
  Q_DECLARE_FLAGS(Properties, Property)

 public:
  explicit ObjectsChangedPropertiesEvent(Object *object, Properties properties);
  explicit ObjectsChangedPropertiesEvent(const QList<Object *> &objects,
                                         Properties properties);
  ~ObjectsChangedPropertiesEvent() override;

  [[nodiscard]] Properties getProperties() const;

 private:
  Properties m_properties;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ObjectsChangedPropertiesEvent::Properties)

class FLOW_DOCUMENT_API ObjectsAddedRemovedEvent : public ObjectsChangedEvent {
 public:
  enum class ObjectsType { Node };

 public:
  ~ObjectsAddedRemovedEvent() override;

  [[nodiscard]] ObjectsType getObjectsType() const;

 protected:
  explicit ObjectsAddedRemovedEvent(const QList<Object *> &objects,
                                    ObjectsType objects_type, Type type);

 private:
  ObjectsType m_objects_type;
};

class FLOW_DOCUMENT_API ObjectsAddedEvent : public ObjectsAddedRemovedEvent {
 public:
  explicit ObjectsAddedEvent(Object *object, ObjectsType objects_type);
  explicit ObjectsAddedEvent(const QList<Object *> &objects,
                             ObjectsType objects_type);
  ~ObjectsAddedEvent() override;
};

class FLOW_DOCUMENT_API ObjectsRemovedEvent : public ObjectsAddedRemovedEvent {
 public:
  explicit ObjectsRemovedEvent(Object *object, ObjectsType objects_type);
  explicit ObjectsRemovedEvent(const QList<Object *> &objects,
                               ObjectsType objects_type);
  ~ObjectsRemovedEvent() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECTS_EVENT_H
