/* ----------------------------------- Local -------------------------------- */
#include "component/properties/math_node_value_properties.h"

#include "command/change_math_node.h"
#include "event/math_node_change_event.h"
#include "flow/math_node_value.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/properties/variant_property_manager.h>
#include <flow_document/flow_document.h>
/* -------------------------------------------------------------------------- */

/* ---------------------- MathNodeDoubleEmitterProperties ------------------- */

MathNodeDoubleEmitterProperties::MathNodeDoubleEmitterProperties(
    QObject* parent)
    : flow_document::NodeProperties(parent) {}

MathNodeDoubleEmitterProperties::~MathNodeDoubleEmitterProperties() = default;

void MathNodeDoubleEmitterProperties::init() {
  flow_document::NodeProperties::init();

  auto prop = getObjectProperties();
  prop->createProperty(Property::Value, QMetaType::Double, tr("Value"));
}

void MathNodeDoubleEmitterProperties::onEvent(
    const flow_document::ChangeEvent& event) {
  flow_document::NodeProperties::onEvent(event);

  if (event.getType() == MathNodeDoubleEmittersChangeEvent::type) {
    auto& e = static_cast<const MathNodeDoubleEmittersChangeEvent&>(event);
    if (e.getNodes().contains(getNode())) update();
  }
}

void MathNodeDoubleEmitterProperties::updateObject() {
  flow_document::NodeProperties::updateObject();

  auto prop = getObjectProperties();
  if (auto node = static_cast<MathNodeDoubleEmitter*>(getNode()); node) {
    prop->getPropertyById(Property::Value)->setValue(node->getValue());
  }
}

void MathNodeDoubleEmitterProperties::applyObject(size_t id,
                                                  const QVariant& value) {
  flow_document::NodeProperties::applyObject(id, value);

  auto node = static_cast<MathNodeDoubleEmitter*>(getNode());

  switch (id) {
    case Property::Value: {
      auto number = value.toDouble();
      if (node->getValue() != number) {
        getDocument()->getUndoStack()->push(
            new SetMathNodeDoubleEmitterValue(getDocument(), {node}, number));
      }

      break;
    }
  }
}