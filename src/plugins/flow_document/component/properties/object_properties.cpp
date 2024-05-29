/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/object_properties.h"

#include "flow_document/component/properties/variant_property_manager.h"
#include "flow_document/event/change_event.h"
#include "flow_document/flow/object.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMetaType>
#include <QScopedValueRollback>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/property_browser/editor_factory.h>
#include <utils/property_browser/property_manager.h>
#include <utils/property_browser/tree_property_browser.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------------- Properties ------------------------------ */

Properties::Properties(const QString& name, QObject* parent)
    : QObject(parent),
      m_group_manager(new utils::QtGroupPropertyManager(this)),
      m_property_manager(new VariantPropertyManager(this)),
      m_editor_factory(new utils::QtVariantEditorFactory(this)),
      m_root(m_group_manager->addProperty(name)) {
  connect(m_property_manager, &VariantPropertyManager::valueChanged, this,
          [this](const auto& property, const auto& value) {
            if (auto opt_id = getIdByProperty(property); opt_id.has_value())
              Q_EMIT valueChanged(*opt_id, value);
          });
}

Properties::~Properties() = default;

utils::QtProperty* Properties::getRoot() const { return m_root; }

qsizetype Properties::size() const { return m_property_to_id.size(); }

bool Properties::contains(utils::QtProperty* property) const {
  if (!property) return false;
  return m_property_to_id.contains(property);
}

void Properties::setFactoryForManager(utils::QtTreePropertyBrowser* browser) {
  browser->setFactoryForManager(m_property_manager, m_editor_factory);
}

void Properties::unsetFactoryForManager(utils::QtTreePropertyBrowser* browser) {
  browser->unsetFactoryForManager(m_property_manager);
}

utils::QtProperty* Properties::createGroup(const QString& name,
                                           utils::QtProperty* parent) {
  auto property = m_group_manager->addProperty(name);

  if (!parent) parent = m_root;
  parent->addSubProperty(property);

  return property;
}

utils::QtVariantProperty* Properties::createProperty(
    size_t id, int type, const QString& name, utils::QtProperty* parent) {
  Q_ASSERT(!m_id_to_property.contains(id));

  auto property = m_property_manager->addProperty(type, name);
  if (!property) {
    property = m_property_manager->addProperty(QMetaType::QString, name);
  }

  if (type == QMetaType::Bool) {
    property->setAttribute(QLatin1String("textVisible"), false);
  }

  m_property_to_id.insert(property, id);
  m_id_to_property.insert(id, property);

  if (!parent) parent = m_root;
  parent->addSubProperty(property);

  return property;
}

utils::QtVariantProperty* Properties::getPropertyById(size_t id) const {
  return m_id_to_property.contains(id) ? m_id_to_property[id] : nullptr;
}

std::optional<size_t> Properties::getIdByProperty(
    utils::QtProperty* property) const {
  if (m_property_to_id.contains(property)) return m_property_to_id[property];
  return std::nullopt;
}

void Properties::clear() {
  m_property_to_id.clear();
  m_id_to_property.clear();
  m_property_manager->clear();
}

/* ----------------------------- ObjectProperties --------------------------- */

ObjectProperties::ObjectProperties(const QString& name, QObject* parent)
    : QObject(parent),
      m_object(nullptr),
      m_document(nullptr),
      m_updating(false),
      m_custom_properties(new Properties(tr("Custom"), this)),
      m_object_properties(new Properties(name, this)) {
  connect(m_custom_properties, &Properties::valueChanged, this,
          [this](auto id, const auto& value) {
            if (!m_updating) applyCustom(id, value);
          });
  connect(m_object_properties, &Properties::valueChanged, this,
          [this](auto id, const auto& value) {
            if (!m_updating) applyObject(id, value);
          });
}

ObjectProperties::~ObjectProperties() = default;

QList<utils::QtProperty*> ObjectProperties::getProperties() const {
  return {m_object_properties->getRoot(), m_custom_properties->getRoot()};
}

void ObjectProperties::setDocument(FlowDocument* document) {
  if (m_document == document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::event, this,
               &ObjectProperties::onEvent);
  }

  m_document = document;

  if (m_document) {
    connect(m_document, &FlowDocument::event, this, &ObjectProperties::onEvent);
  }
}

FlowDocument* ObjectProperties::getDocument() const { return m_document; }

void ObjectProperties::setObject(Object* object) {
  if (m_object == object) return;

  m_object = object;

  update();
}

Object* ObjectProperties::getObject() const { return m_object; }

bool ObjectProperties::isCustomProperty(utils::QtProperty* property) const {
  return m_custom_properties->contains(property);
}

void ObjectProperties::setFactoryForManager(
    utils::QtTreePropertyBrowser* browser) {
  m_custom_properties->setFactoryForManager(browser);
  m_object_properties->setFactoryForManager(browser);
}

void ObjectProperties::unsetFactoryForManager(
    utils::QtTreePropertyBrowser* browser) {
  m_custom_properties->unsetFactoryForManager(browser);
  m_object_properties->unsetFactoryForManager(browser);
}

void ObjectProperties::onEvent(const ChangeEvent& event) {}

void ObjectProperties::applyCustom(size_t id, const QVariant& value) {
  auto property = m_custom_properties->getPropertyById(id);
  if (!property) return;

  auto property_name = property->propertyName();
  applyCustom(property_name, value);
}

void ObjectProperties::applyCustom(const QString& name, const QVariant& value) {
}

void ObjectProperties::applyObject(size_t id, const QVariant& value) {}

Properties* ObjectProperties::getCustomProperties() const {
  return m_custom_properties;
}

Properties* ObjectProperties::getObjectProperties() const {
  return m_object_properties;
}

void ObjectProperties::update() {
  QScopedValueRollback<bool> updating(m_updating, true);

  updateCustom();
  updateObject();
}

void ObjectProperties::updateCustom() {
  if (!m_object) return;

  const auto& properties = m_object->getProperties();
  if (m_custom_properties->size() != properties.size()) {
    m_custom_properties->clear();
  }

  for (const auto& key : properties.keys()) {
    const auto id = qHash(key);
    auto property = m_custom_properties->getPropertyById(id);

    if (!property) {
      const auto type_id = properties[key].typeId();
      property = m_custom_properties->createProperty(id, type_id, key);
    }

    property->setValue(properties[key]);
  }
}

void ObjectProperties::updateObject() {}

}  // namespace flow_document