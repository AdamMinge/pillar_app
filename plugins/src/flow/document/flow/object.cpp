/* ----------------------------------- Local -------------------------------- */
#include "flow/document/flow/object.h"
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/serializer/archive.h>
#include <qtils/serializer/archive_property.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ----------------------------------- Object ------------------------------- */

Object::Object() : m_id(QUuid::createUuid()) {}

Object::~Object() = default;

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

void Object::serialize(qtils::OArchive &archive) const {
  archive << qtils::ArchiveProperty("id", m_id);
  archive << qtils::ArchiveProperty("name", m_name);
  archive << qtils::ArchiveProperty("properties", m_properties);
}

void Object::deserialize(qtils::IArchive &archive) {
  archive >> qtils::ArchiveProperty("id", m_id);
  archive >> qtils::ArchiveProperty("name", m_name);
  archive >> qtils::ArchiveProperty("properties", m_properties);
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
}

/* ------------------------------- MoveableObject --------------------------- */

MoveableObject::MoveableObject() = default;

MoveableObject::~MoveableObject() = default;

void MoveableObject::setPosition(const QPointF &position) {
  m_position = position;
}

QPointF MoveableObject::getPosition() const { return m_position; }

void MoveableObject::serialize(qtils::OArchive &archive) const {
  Object::serialize(archive);

  archive << qtils::ArchiveProperty("position", m_position);
}

void MoveableObject::deserialize(qtils::IArchive &archive) {
  Object::deserialize(archive);

  archive >> qtils::ArchiveProperty("position", m_position);
}

void MoveableObject::init(const MoveableObject *object) {
  Object::init(object);

  m_position = object->m_position;
}

}  // namespace flow
