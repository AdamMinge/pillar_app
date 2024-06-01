/* ----------------------------------- Local -------------------------------- */
#include "component/properties/math_node_value_properties.h"

#include "command/change_math_node.h"
#include "event/math_node_change_event.h"
#include "flow/math_node_value.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/properties/variant_property_manager.h>
#include <flow_document/flow_document.h>
/* -------------------------------------------------------------------------- */

/* ---------------------- MathNodeFloatEmitterProperties -------------------- */

MathNodeFloatEmitterProperties::MathNodeFloatEmitterProperties(QObject* parent)
    : flow_document::NodeProperties(parent) {}

MathNodeFloatEmitterProperties::~MathNodeFloatEmitterProperties() = default;

void MathNodeFloatEmitterProperties::init() {
  flow_document::NodeProperties::init();

  auto prop = getObjectProperties();
  prop->createProperty(Property::Value, QMetaType::Double, tr("Value"));
}

void MathNodeFloatEmitterProperties::onEvent(
    const flow_document::ChangeEvent& event) {
  flow_document::NodeProperties::onEvent(event);

  if (event.getType() == MathNodeFloatEmittersChangeEvent::type) {
    auto& e = static_cast<const MathNodeFloatEmittersChangeEvent&>(event);
    if (e.getNodes().contains(getNode())) update();
  }
}

void MathNodeFloatEmitterProperties::updateObject() {
  flow_document::NodeProperties::updateObject();

  auto prop = getObjectProperties();
  if (auto node = static_cast<MathNodeFloatEmitter*>(getNode()); node) {
    prop->getPropertyById(Property::Value)->setValue(node->getValue());
  }
}

void MathNodeFloatEmitterProperties::applyObject(size_t id,
                                                 const QVariant& value) {
  flow_document::NodeProperties::applyObject(id, value);

  auto node = static_cast<MathNodeFloatEmitter*>(getNode());

  switch (id) {
    case Property::Value: {
      auto number = value.toFloat();
      if (node->getValue() != number) {
        getDocument()->getUndoStack()->push(
            new SetMathNodeFloatEmitterValue(getDocument(), {node}, number));
      }

      break;
    }
  }
}