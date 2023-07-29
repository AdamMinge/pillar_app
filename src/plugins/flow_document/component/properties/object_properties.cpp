/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/object_properties.h"

#include "flow_document/command/change_connection.h"
#include "flow_document/command/change_layer.h"
#include "flow_document/command/change_node.h"
#include "flow_document/component/properties/variant_property_manager.h"
#include "flow_document/event/change_event.h"
#include "flow_document/event/connection_change_event.h"
#include "flow_document/event/layer_change_event.h"
#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/node.h"
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

/* ------------------------------ LayerProperties --------------------------- */

LayerProperties::LayerProperties(QObject* parent)
    : ObjectProperties(tr("Layer"), parent) {
  initLayerProperty();
}

LayerProperties::~LayerProperties() = default;

Layer* LayerProperties::getLayer() const {
  return static_cast<Layer*>(getObject());
}

void LayerProperties::addProperty(const QString& name, const QVariant& value) {
  getDocument()->getUndoStack()->push(new AddLayersProperties(
      getDocument(), {getLayer()}, {std::make_pair(name, value)}));
}

void LayerProperties::removeProperty(const QString& name) {
  getDocument()->getUndoStack()->push(
      new RemoveLayersProperties(getDocument(), {getLayer()}, {name}));
}

void LayerProperties::onEvent(const ChangeEvent& event) {
  if (event.getType() == LayersChangeEvent::type) {
    const auto& e = static_cast<const LayersChangeEvent&>(event);
    if (e.getLayers().contains(getLayer())) update();
  }
}

void LayerProperties::updateObject() {
  auto prop = getObjectProperties();
  if (auto layer = getLayer(); layer) {
    prop->getPropertyById(Property::Name)->setValue(layer->getName());
    prop->getPropertyById(Property::Visible)->setValue(layer->isVisible());
    prop->getPropertyById(Property::Locked)->setValue(layer->isLocked());
    prop->getPropertyById(Property::Opacity)->setValue(layer->getOpacity());
    prop->getPropertyById(Property::Position)->setValue(layer->getPosition());
  }
}

void LayerProperties::applyCustom(const QString& name, const QVariant& value) {
  getDocument()->getUndoStack()->push(
      new SetLayersCustomProperty(getDocument(), {getLayer()}, name, value));
}

void LayerProperties::applyObject(size_t id, const QVariant& value) {
  auto layer = getLayer();

  switch (id) {
    case Property::Name: {
      auto name = value.toString();
      if (layer->getName() != name) {
        getDocument()->getUndoStack()->push(
            new SetLayersName(getDocument(), {layer}, name));
      }

      break;
    }

    case Property::Visible: {
      getDocument()->getUndoStack()->push(
          new SetLayersVisible(getDocument(), {layer}, value.toBool()));
      break;
    }

    case Property::Locked: {
      getDocument()->getUndoStack()->push(
          new SetLayersLocked(getDocument(), {layer}, value.toBool()));
      break;
    }

    case Property::Opacity: {
      getDocument()->getUndoStack()->push(
          new SetLayersOpacity(getDocument(), {layer}, value.toReal()));
      break;
    }

    case Property::Position: {
      getDocument()->getUndoStack()->push(
          new SetLayersPosition(getDocument(), {layer}, value.toPointF()));
      break;
    }
  }
}

void LayerProperties::initLayerProperty() {
  auto prop = getObjectProperties();
  prop->createProperty(Property::Name, QMetaType::QString, tr("Name"));
  prop->createProperty(Property::Visible, QMetaType::Bool, tr("Visible"));
  prop->createProperty(Property::Locked, QMetaType::Bool, tr("Locked"));
  prop->createProperty(Property::Opacity, QMetaType::QReal, tr("Opacity"));
  prop->createProperty(Property::Position, QMetaType::QPointF, tr("Position"));
}

/* ------------------------------ NodeProperties ---------------------------- */

NodeProperties::NodeProperties(QObject* parent)
    : ObjectProperties(tr("Node"), parent) {
  initNodeProperty();
}

NodeProperties::~NodeProperties() = default;

Node* NodeProperties::getNode() const {
  return static_cast<Node*>(getObject());
}

void NodeProperties::addProperty(const QString& name, const QVariant& value) {
  getDocument()->getUndoStack()->push(new AddNodesProperties(
      getDocument(), {getNode()}, {std::make_pair(name, value)}));
}

void NodeProperties::removeProperty(const QString& name) {
  getDocument()->getUndoStack()->push(
      new RemoveNodesProperties(getDocument(), {getNode()}, {name}));
}

void NodeProperties::onEvent(const ChangeEvent& event) {
  if (event.getType() == NodesChangeEvent::type) {
    auto& e = static_cast<const NodesChangeEvent&>(event);
    if (e.getNodes().contains(getNode())) update();
  }
}

void NodeProperties::updateObject() {
  auto prop = getObjectProperties();
  if (auto node = getNode(); node) {
    prop->getPropertyById(Property::Name)->setValue(node->getName());
    prop->getPropertyById(Property::Visible)->setValue(node->isVisible());
    prop->getPropertyById(Property::Position)->setValue(node->getPosition());
  }
}

void NodeProperties::applyCustom(const QString& name, const QVariant& value) {
  getDocument()->getUndoStack()->push(
      new SetNodesCustomProperty(getDocument(), {getNode()}, name, value));
}

void NodeProperties::applyObject(size_t id, const QVariant& value) {
  auto node = getNode();

  switch (id) {
    case Property::Name: {
      auto name = value.toString();
      if (node->getName() != name) {
        getDocument()->getUndoStack()->push(
            new SetNodesName(getDocument(), {node}, name));
      }

      break;
    }

    case Property::Visible: {
      getDocument()->getUndoStack()->push(
          new SetNodesVisible(getDocument(), {node}, value.toBool()));
      break;
    }

    case Property::Position: {
      getDocument()->getUndoStack()->push(
          new SetNodesPosition(getDocument(), {node}, value.toPointF()));
      break;
    }
  }
}

void NodeProperties::initNodeProperty() {
  auto prop = getObjectProperties();
  prop->createProperty(Property::Name, QMetaType::QString, tr("Name"));
  prop->createProperty(Property::Visible, QMetaType::Bool, tr("Visible"));
  prop->createProperty(Property::Position, QMetaType::QPointF, tr("Position"));
}

/* --------------------------- ConnectionProperties ------------------------- */

ConnectionProperties::ConnectionProperties(QObject* parent)
    : ObjectProperties(tr("Connection"), parent) {
  initConnectionProperty();
}

ConnectionProperties::~ConnectionProperties() = default;

Connection* ConnectionProperties::getConnection() const {
  return static_cast<Connection*>(getObject());
}

void ConnectionProperties::addProperty(const QString& name,
                                       const QVariant& value) {
  getDocument()->getUndoStack()->push(new AddConnectionsProperties(
      getDocument(), {getConnection()}, {std::make_pair(name, value)}));
}

void ConnectionProperties::removeProperty(const QString& name) {
  getDocument()->getUndoStack()->push(new RemoveConnectionsProperties(
      getDocument(), {getConnection()}, {name}));
}

void ConnectionProperties::onEvent(const ChangeEvent& event) {
  if (event.getType() == ConnectionsChangeEvent::type) {
    auto& e = static_cast<const ConnectionsChangeEvent&>(event);
    if (e.getConnections().contains(getConnection())) update();
  }
}

void ConnectionProperties::updateObject() {
  auto prop = getObjectProperties();
  if (auto connection = getConnection(); connection) {
    prop->getPropertyById(Property::Name)->setValue(connection->getName());
    prop->getPropertyById(Property::Visible)->setValue(connection->isVisible());
  }
}

void ConnectionProperties::applyCustom(const QString& name,
                                       const QVariant& value) {
  getDocument()->getUndoStack()->push(new SetConnectionsCustomProperty(
      getDocument(), {getConnection()}, name, value));
}

void ConnectionProperties::applyObject(size_t id, const QVariant& value) {
  auto connection = getConnection();

  switch (id) {
    case Property::Name: {
      auto name = value.toString();
      if (connection->getName() != name) {
        getDocument()->getUndoStack()->push(
            new SetConnectionsName(getDocument(), {connection}, name));
      }

      break;
    }

    case Property::Visible: {
      getDocument()->getUndoStack()->push(new SetConnectionsVisible(
          getDocument(), {connection}, value.toBool()));
      break;
    }
  }
}

void ConnectionProperties::initConnectionProperty() {
  auto prop = getObjectProperties();
  prop->createProperty(Property::Name, QMetaType::QString, tr("Name"));
  prop->createProperty(Property::Visible, QMetaType::Bool, tr("Visible"));
}

}  // namespace flow_document