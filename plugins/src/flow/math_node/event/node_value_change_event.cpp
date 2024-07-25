/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/event/node_value_change_event.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* --------------------- MathNodeDoubleEmittersChangeEvent ------------------ */

MathNodeDoubleEmittersChangeEvent::MathNodeDoubleEmittersChangeEvent(
    QList<MathNodeDoubleEmitter*> nodes, Properties properties)
    : ChangeEvent(type), m_nodes(std::move(nodes)), m_properties(properties) {}

MathNodeDoubleEmittersChangeEvent::~MathNodeDoubleEmittersChangeEvent() =
    default;

const QList<MathNodeDoubleEmitter*>&
MathNodeDoubleEmittersChangeEvent::getNodes() const {
  return m_nodes;
}

MathNodeDoubleEmittersChangeEvent::Properties
MathNodeDoubleEmittersChangeEvent::getProperties() const {
  return m_properties;
}

bool MathNodeDoubleEmittersChangeEvent::contains(
    MathNodeDoubleEmitter* node) const {
  return m_nodes.contains(node);
}

}  // namespace flow