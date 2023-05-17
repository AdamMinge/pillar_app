/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Object::Object(Type type) : m_id(QUuid::createUuid()), m_type(type) {}

Object::~Object() = default;

Object::Type Object::getType() const { return m_type; }

QUuid Object::getId() const { return m_id; }

void Object::setName(const QString &name) { m_name = name; }

QString Object::getName() const { return m_name; }

void Object::setProperties(const QVariantMap &properties) {
  m_properties = properties;
}

const QVariantMap &Object::getProperties() const { return m_properties; }

}  // namespace flow_document
