#ifndef FLOW_DOCUMENT_CHANGE_EVENT_H
#define FLOW_DOCUMENT_CHANGE_EVENT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API ChangeEvent {
 public:
  enum class Type { ObjectsAdded, ObjectsRemoved, ObjectsChangedProperties };

 public:
  explicit ChangeEvent(Type type);
  virtual ~ChangeEvent();

  [[nodiscard]] Type getType() const;

 private:
  Type m_type;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CHANGE_EVENT_H
