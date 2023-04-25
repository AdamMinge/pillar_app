/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/flow_object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowObject::FlowObject() = default;

FlowObject::~FlowObject() = default;

void FlowObject::setName(const QString &name) { m_name = name; }

QString FlowObject::getName() const { return m_name; }

void FlowObject::setPosition(const QPointF &position) { m_position = position; }

QPointF FlowObject::getPosition() const { return m_position; }

void FlowObject::setProperties(const QVariantMap &properties) {
  m_properties = properties;
}

const QVariantMap &FlowObject::getProperties() const { return m_properties; }

}  // namespace flow_document
