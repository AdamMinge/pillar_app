/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/object.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

Object::Object(Type type) : m_id(QUuid::createUuid()), m_type(type) {}

Object::~Object() = default;

Object::Type Object::getType() const { return m_type; }

QUuid Object::getId() const { return m_id; }

void Object::setName(const QString &name) { m_name = name; }

QString Object::getName() const { return m_name; }

void Object::setProperty(const QString &name, const QVariant &value) {
  m_properties[name] = value;
}

QVariant Object::getProperty(const QString &name) const {
  return m_properties.contains(name) ? m_properties[name] : QVariant{};
}

void Object::removeProperty(const QString &name) { m_properties.remove(name); }

void Object::setProperties(const QVariantMap &properties) {
  m_properties = properties;
}

const QVariantMap &Object::getProperties() const { return m_properties; }

void Object::serialize(utils::OArchive &archive) const {
  archive << utils::ArchiveProperty("id", m_id);
  archive << utils::ArchiveProperty("name", m_name);
  archive << utils::ArchiveProperty("properties", m_properties);
}

void Object::deserialize(utils::IArchive &archive) {}

void Object::init(const Object *object) {
  m_name = object->m_name;
  m_properties = object->m_properties;
}

}  // namespace flow_document
