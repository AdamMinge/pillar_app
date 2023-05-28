/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/object_properties.h"

#include "flow_document/component/properties/variant_property_manager.h"
#include "flow_document/event/change_event.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/node.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMetaType>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/property_browser/property_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------- ObjectProperties --------------------------- */

ObjectProperties::ObjectProperties(QObject* parent)
    : QObject(parent),
      m_object(nullptr),
      m_group_property_manager(new utils::QtGroupPropertyManager(this)),
      m_variant_property_manager(new VariantPropertyManager(this)) {}

ObjectProperties::~ObjectProperties() = default;

void ObjectProperties::setObject(Object* object) {
  if (m_object == object) return;

  m_object = object;
}

Object* ObjectProperties::getObject() const { return m_object; }

utils::QtProperty* ObjectProperties::getRootProperty() {
  if (!m_root_property) {
    m_root_property = createGroup(QLatin1String{});

    if (auto object_property = createObjectProperty())
      m_root_property->addSubProperty(object_property);
    if (auto custom_property = createCustomProperty())
      m_root_property->addSubProperty(custom_property);
  }

  return m_root_property;
}

void ObjectProperties::onEvent(const ChangeEvent& event) {}

utils::QtProperty* ObjectProperties::createObjectProperty() { return nullptr; }

utils::QtProperty* ObjectProperties::createCustomProperty() { return nullptr; }

utils::QtProperty* ObjectProperties::createGroup(const QString& name) {
  return m_group_property_manager->addProperty(name);
}

utils::QtProperty* ObjectProperties::createProperty(int id, TypeId type,
                                                    const QString& name) {
  Q_ASSERT(!m_id_to_property.contains(id));

  auto property = m_variant_property_manager->addProperty(type, name);
  if (!property) {
    property =
        m_variant_property_manager->addProperty(QMetaType::QString, name);
  }

  if (type == QMetaType::Bool) {
    property->setAttribute(QLatin1String("textVisible"), false);
  }

  m_property_to_id.insert(property, id);
  m_id_to_property.insert(id, property);

  return property;
}

utils::QtProperty* ObjectProperties::addProperty(int id, TypeId type,
                                                 const QString& name,
                                                 utils::QtProperty* parent) {
  auto property = createProperty(id, type, name);
  parent->addSubProperty(property);

  return property;
}

/* ------------------------------ LayerProperties --------------------------- */

LayerProperties::LayerProperties(QObject* parent) : ObjectProperties(parent) {}

LayerProperties::~LayerProperties() = default;

QString LayerProperties::supportedClass() const {
  return Layer::staticClassName();
}

void LayerProperties::onEvent(const ChangeEvent& event) {}

utils::QtProperty* LayerProperties::createObjectProperty() { return nullptr; }

/* ------------------------------ NodeProperties ---------------------------- */

NodeProperties::NodeProperties(QObject* parent) : ObjectProperties(parent) {}

NodeProperties::~NodeProperties() = default;

QString NodeProperties::supportedClass() const {
  return Node::staticClassName();
}

void NodeProperties::onEvent(const ChangeEvent& event) {}

utils::QtProperty* NodeProperties::createObjectProperty() { return nullptr; }

}  // namespace flow_document