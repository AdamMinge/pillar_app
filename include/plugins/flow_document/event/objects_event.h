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

class FlowObject;

class FLOW_DOCUMENT_API ObjectsChangedEvent : public ChangeEvent {
 public:
  explicit ObjectsChangedEvent(const QList<FlowObject *> &objects, Type type);
  virtual ~ObjectsChangedEvent();

  [[nodiscard]] QList<FlowObject *> getObjects() const;
  [[nodiscard]] bool contains(FlowObject *object) const;

 private:
  QList<FlowObject *> m_objects;
};

class FLOW_DOCUMENT_API ObjectsChangedPropertiesEvent
    : public ObjectsChangedEvent {
 public:
  enum class Property { PositionProperty, CustomProperty };
  Q_DECLARE_FLAGS(Properties, Property)

 public:
  explicit ObjectsChangedPropertiesEvent(FlowObject *object,
                                         Properties properties);
  explicit ObjectsChangedPropertiesEvent(const QList<FlowObject *> &objects,
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
  explicit ObjectsAddedRemovedEvent(const QList<FlowObject *> &objects,
                                    ObjectsType objects_type, Type type);

 private:
  ObjectsType m_objects_type;
};

class FLOW_DOCUMENT_API ObjectsAddedEvent : public ObjectsAddedRemovedEvent {
 public:
  explicit ObjectsAddedEvent(FlowObject *object, ObjectsType objects_type);
  explicit ObjectsAddedEvent(const QList<FlowObject *> &objects,
                             ObjectsType objects_type);
  ~ObjectsAddedEvent() override;
};

class FLOW_DOCUMENT_API ObjectsRemovedEvent : public ObjectsAddedRemovedEvent {
 public:
  explicit ObjectsRemovedEvent(FlowObject *object, ObjectsType objects_type);
  explicit ObjectsRemovedEvent(const QList<FlowObject *> &objects,
                               ObjectsType objects_type);
  ~ObjectsRemovedEvent() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECTS_EVENT_H
