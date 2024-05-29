/* ----------------------------------- Local -------------------------------- */
#include "event/math_node_change_event.h"
/* -------------------------------------------------------------------------- */

/* --------------------- MathNodeFloatEmittersChangeEvent ------------------- */

MathNodeFloatEmittersChangeEvent::MathNodeFloatEmittersChangeEvent(
    QList<MathNodeFloatEmitter*> nodes, Properties properties)
    : ChangeEvent(type), m_nodes(std::move(nodes)), m_properties(properties) {}

MathNodeFloatEmittersChangeEvent::~MathNodeFloatEmittersChangeEvent() = default;

const QList<MathNodeFloatEmitter*>& MathNodeFloatEmittersChangeEvent::getNodes()
    const {
  return m_nodes;
}

MathNodeFloatEmittersChangeEvent::Properties
MathNodeFloatEmittersChangeEvent::getProperties() const {
  return m_properties;
}

bool MathNodeFloatEmittersChangeEvent::contains(
    MathNodeFloatEmitter* node) const {
  return m_nodes.contains(node);
}