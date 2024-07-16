/* ----------------------------------- Local -------------------------------- */
#include "event/logic_node_change_event.h"
/* -------------------------------------------------------------------------- */

/* --------------------- LogicNodeBoolEmittersChangeEvent ------------------- */

LogicNodeBoolEmittersChangeEvent::LogicNodeBoolEmittersChangeEvent(
    QList<LogicNodeBoolEmitter*> nodes, Properties properties)
    : ChangeEvent(type), m_nodes(std::move(nodes)), m_properties(properties) {}

LogicNodeBoolEmittersChangeEvent::~LogicNodeBoolEmittersChangeEvent() = default;

const QList<LogicNodeBoolEmitter*>& LogicNodeBoolEmittersChangeEvent::getNodes()
    const {
  return m_nodes;
}

LogicNodeBoolEmittersChangeEvent::Properties
LogicNodeBoolEmittersChangeEvent::getProperties() const {
  return m_properties;
}

bool LogicNodeBoolEmittersChangeEvent::contains(
    LogicNodeBoolEmitter* node) const {
  return m_nodes.contains(node);
}