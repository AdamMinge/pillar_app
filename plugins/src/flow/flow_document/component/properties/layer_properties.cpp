/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/layer_properties.h"

#include "flow_document/command/change_layer.h"
#include "flow_document/component/properties/variant_property_manager.h"
#include "flow_document/event/layer_change_event.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------ LayerProperties --------------------------- */

LayerProperties::LayerProperties(QObject* parent)
    : ObjectProperties(tr("Layer"), parent) {}

LayerProperties::~LayerProperties() = default;

void LayerProperties::init() {
  auto prop = getObjectProperties();
  prop->createProperty(Property::Name, QMetaType::QString, tr("Name"));
  prop->createProperty(Property::Visible, QMetaType::Bool, tr("Visible"));
  prop->createProperty(Property::Locked, QMetaType::Bool, tr("Locked"));
  prop->createProperty(Property::Opacity, QMetaType::QReal, tr("Opacity"));
  prop->createProperty(Property::Position, QMetaType::QPointF, tr("Position"));
}

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

}  // namespace flow_document