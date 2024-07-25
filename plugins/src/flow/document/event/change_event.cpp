/* ----------------------------------- Local -------------------------------- */
#include "flow/document/event/change_event.h"
/* -------------------------------------------------------------------------- */

namespace flow {

ChangeEvent::ChangeEvent(QString type) : m_type(std::move(type)) {}

ChangeEvent::~ChangeEvent() = default;

QString ChangeEvent::getType() const { return m_type; }

}  // namespace flow