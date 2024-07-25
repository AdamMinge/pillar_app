/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/event/node_value_change_event.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* -------------------- StringNodeStringEmittersChangeEvent ----------------- */

StringNodeStringEmittersChangeEvent::StringNodeStringEmittersChangeEvent(
    QList<StringNodeStringEmitter*> nodes, Properties properties)
    : ChangeEvent(type), m_nodes(std::move(nodes)), m_properties(properties) {}

StringNodeStringEmittersChangeEvent::~StringNodeStringEmittersChangeEvent() =
    default;

const QList<StringNodeStringEmitter*>&
StringNodeStringEmittersChangeEvent::getNodes() const {
  return m_nodes;
}

StringNodeStringEmittersChangeEvent::Properties
StringNodeStringEmittersChangeEvent::getProperties() const {
  return m_properties;
}

bool StringNodeStringEmittersChangeEvent::contains(
    StringNodeStringEmitter* node) const {
  return m_nodes.contains(node);
}

}  // namespace flow