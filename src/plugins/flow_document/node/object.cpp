/* ----------------------------------- Local -------------------------------- */
#include "flow_document/node/object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Object::Object() = default;

Object::~Object() = default;

void Object::setName(const QString &name) { m_name = name; }

QString Object::getName() const { return m_name; }

void Object::setPosition(const QPointF &position) { m_position = position; }

QPointF Object::getPosition() const { return m_position; }

void Object::setProperties(const QVariantMap &properties) {
  m_properties = properties;
}

const QVariantMap &Object::getProperties() const { return m_properties; }

}  // namespace flow_document
