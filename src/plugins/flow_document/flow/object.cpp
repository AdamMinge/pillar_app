/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/object.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/serializer/archive.h>
#include <utils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

Object::Object() : m_id(QUuid::createUuid()), m_visible(true) {}

Object::~Object() = default;

QUuid Object::getId() const { return m_id; }

void Object::setName(const QString &name) { m_name = name; }

QString Object::getName() const { return m_name; }

void Object::setVisible(bool visible) { m_visible = visible; }

bool Object::isVisible() const { return m_visible; }

void Object::setPosition(const QPointF &position) { m_position = position; }

QPointF Object::getPosition() const { return m_position; }

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
  archive << utils::ArchiveProperty("position", m_position);
  archive << utils::ArchiveProperty("visible", m_visible);
  archive << utils::ArchiveProperty("properties", m_properties);
}

void Object::deserialize(utils::IArchive &archive) {
  archive >> utils::ArchiveProperty("id", m_id);
  archive >> utils::ArchiveProperty("name", m_name);
  archive >> utils::ArchiveProperty("position", m_position);
  archive >> utils::ArchiveProperty("visible", m_visible);
  archive >> utils::ArchiveProperty("properties", m_properties);
}

QString Object::sGetClassName() { return "Object"; }

QString Object::getClassName() const { return "Object"; }

QString Object::sGetParentClassName() { return ""; }

QString Object::getParentClassName() const { return ""; }

QStringList Object::sGetInheritedClassNames() { return {}; }

QStringList Object::getInheritedClassNames() const { return {}; }

bool Object::sIsClass(const QString &className) {
  return Object::sGetClassName() == className;
}

bool Object::isClass(const QString &className) const {
  return getClassName() == className;
}

bool Object::sIsClassOrChild(const QString &class_name) {
  return Object::sIsClass(class_name);
}

bool Object::isClassOrChild(const QString &class_name) const {
  return isClass(class_name);
}

void Object::init(const Object *object) {
  m_name = object->m_name;
  m_properties = object->m_properties;
  m_position = object->m_position;
  m_visible = object->m_visible;
}

}  // namespace flow_document
