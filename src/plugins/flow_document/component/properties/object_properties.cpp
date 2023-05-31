/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/object_properties.h"

#include "flow_document/command/change_layer.h"
#include "flow_document/command/change_node.h"
#include "flow_document/component/properties/variant_property_manager.h"
#include "flow_document/event/change_event.h"
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

/* ----------------------------- ObjectProperties --------------------------- */

ObjectProperties::ObjectProperties(QObject* parent)
    : QObject(parent),
      m_object(nullptr),
      m_document(nullptr),
      m_updating(false),
      m_group_property_manager(new utils::QtGroupPropertyManager(this)),
      m_variant_property_manager(new VariantPropertyManager(this)),
      m_variant_editor_factory(new utils::QtVariantEditorFactory(this)),
      m_customProperty(createCustomProperty()) {
  connect(m_variant_property_manager, &VariantPropertyManager::valueChanged,
          this, [this](auto property, auto value) {
            if (m_updating) return;
            applyValue(property, value);
          });
}

ObjectProperties::~ObjectProperties() = default;

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

void ObjectProperties::setFactoryForManager(
    utils::QtTreePropertyBrowser* browser) {
  browser->setFactoryForManager(m_variant_property_manager,
                                m_variant_editor_factory);
}

void ObjectProperties::unsetFactoryForManager(
    utils::QtTreePropertyBrowser* browser) {
  browser->unsetFactoryForManager(m_variant_property_manager);
}

void ObjectProperties::onEvent(const ChangeEvent& event) {}

void ObjectProperties::update() {
  QScopedValueRollback<bool> updating(m_updating, true);

  updateObject();
  updateCustom();
}

void ObjectProperties::updateObject() {}

void ObjectProperties::updateCustom() {}

void ObjectProperties::applyValue(utils::QtProperty* property, QVariant value) {
}

utils::QtProperty* ObjectProperties::createGroup(const QString& name,
                                                 utils::QtProperty* parent) {
  auto property = m_group_property_manager->addProperty(name);
  if (parent) parent->addSubProperty(property);
  return property;
}

utils::QtVariantProperty* ObjectProperties::createProperty(
    int id, int type, const QString& name, utils::QtProperty* parent) {
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

  if (parent) parent->addSubProperty(property);

  return property;
}

utils::QtProperty* ObjectProperties::getCustomProperty() const {
  return m_customProperty;
}

utils::QtProperty* ObjectProperties::createCustomProperty(
    utils::QtProperty* parent) {
  auto custom_group = createGroup(tr("Custom"));
  if (parent) parent->addSubProperty(custom_group);

  return custom_group;
}

utils::QtVariantProperty* ObjectProperties::getPropertyById(int id) const {
  return m_id_to_property.contains(id) ? m_id_to_property[id] : nullptr;
}

int ObjectProperties::getIdByProperty(utils::QtProperty* property) const {
  return m_property_to_id.contains(property) ? m_property_to_id[property] : -1;
}

/* ------------------------------ LayerProperties --------------------------- */

LayerProperties::LayerProperties(QObject* parent)
    : ObjectProperties(parent), m_layerProperty(createLayerProperty()) {}

LayerProperties::~LayerProperties() = default;

QList<utils::QtProperty*> LayerProperties::getProperties() const {
  return {m_layerProperty, getCustomProperty()};
}

Layer* LayerProperties::getLayer() const {
  return static_cast<Layer*>(getObject());
}

void LayerProperties::onEvent(const ChangeEvent& event) {
  if (event.getType() == ChangeEvent::Type::LayersChanged) {
    const auto& e = static_cast<const LayersChangeEvent&>(event);
    if (e.getLayers().contains(getLayer())) update();
  }
}

void LayerProperties::updateObject() {
  if (auto layer = getLayer(); layer) {
    getPropertyById(Property::Name)->setValue(layer->getName());
    getPropertyById(Property::Visible)->setValue(layer->isVisible());
    getPropertyById(Property::Locked)->setValue(layer->isLocked());
    getPropertyById(Property::Opacity)->setValue(layer->getOpacity());
    getPropertyById(Property::Position)->setValue(layer->getPosition());
  }
}

void LayerProperties::applyValue(utils::QtProperty* property, QVariant value) {
  switch (getIdByProperty(property)) {
    case Property::Name: {
      getDocument()->getUndoStack()->push(
          new SetLayersName(getDocument(), {getLayer()}, value.toString()));
      break;
    }

    case Property::Visible: {
      getDocument()->getUndoStack()->push(
          new SetLayersVisible(getDocument(), {getLayer()}, value.toBool()));
      break;
    }

    case Property::Locked: {
      getDocument()->getUndoStack()->push(
          new SetLayersLocked(getDocument(), {getLayer()}, value.toBool()));
      break;
    }

    case Property::Opacity: {
      getDocument()->getUndoStack()->push(
          new SetLayersOpacity(getDocument(), {getLayer()}, value.toReal()));
      break;
    }

    case Property::Position: {
      getDocument()->getUndoStack()->push(
          new SetLayersPosition(getDocument(), {getLayer()}, value.toPointF()));
      break;
    }
  }
}

utils::QtProperty* LayerProperties::createLayerProperty() {
  auto object_group = createGroup(tr("Layer"));

  createProperty(Property::Name, QMetaType::QString, tr("Name"), object_group);
  createProperty(Property::Visible, QMetaType::Bool, tr("Visible"),
                 object_group);
  createProperty(Property::Locked, QMetaType::Bool, tr("Locked"), object_group);
  createProperty(Property::Opacity, QMetaType::QReal, tr("Opacity"),
                 object_group);
  createProperty(Property::Position, QMetaType::QPointF, tr("Position"),
                 object_group);

  return object_group;
}

/* ------------------------------ NodeProperties ---------------------------- */

NodeProperties::NodeProperties(QObject* parent)
    : ObjectProperties(parent), m_nodeProperty(createNodeProperty()) {}

NodeProperties::~NodeProperties() = default;

QList<utils::QtProperty*> NodeProperties::getProperties() const {
  return {m_nodeProperty, getCustomProperty()};
}

Node* NodeProperties::getNode() const {
  return static_cast<Node*>(getObject());
}

void NodeProperties::onEvent(const ChangeEvent& event) {
  if (event.getType() == ChangeEvent::Type::NodesChanged) {
    auto& e = static_cast<const NodesChangeEvent&>(event);
    if (e.getNodes().contains(getNode())) update();
  }
}

void NodeProperties::updateObject() {
  if (auto node = getNode(); node) {
    getPropertyById(Property::Name)->setValue(node->getName());
    getPropertyById(Property::Visible)->setValue(node->isVisible());
    getPropertyById(Property::Position)->setValue(node->getPosition());
  }
}

void NodeProperties::applyValue(utils::QtProperty* property, QVariant value) {
  switch (getIdByProperty(property)) {
    case Property::Name: {
      getDocument()->getUndoStack()->push(
          new SetNodesName(getDocument(), {getNode()}, value.toString()));
      break;
    }

    case Property::Visible: {
      getDocument()->getUndoStack()->push(
          new SetNodesVisible(getDocument(), {getNode()}, value.toBool()));
      break;
    }

    case Property::Position: {
      getDocument()->getUndoStack()->push(
          new SetNodesPosition(getDocument(), {getNode()}, value.toPointF()));
      break;
    }
  }
}

utils::QtProperty* NodeProperties::createNodeProperty() {
  auto object_group = createGroup(tr("Node"));

  createProperty(Property::Name, QMetaType::QString, tr("Name"), object_group);
  createProperty(Property::Visible, QMetaType::Bool, tr("Visible"),
                 object_group);
  createProperty(Property::Position, QMetaType::QPointF, tr("Position"),
                 object_group);

  return object_group;
}

}  // namespace flow_document