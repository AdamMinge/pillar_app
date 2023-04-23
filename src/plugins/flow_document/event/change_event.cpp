/* ----------------------------------- Local -------------------------------- */
#include "flow_document/event/change_event.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

ChangeEvent::ChangeEvent(Type type) : m_type(type) {}

ChangeEvent::~ChangeEvent() = default;

ChangeEvent::Type ChangeEvent::getType() const { return m_type; }

}  // namespace flow_document