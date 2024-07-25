/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/component/properties/node_value_properties.h"

#include "flow/math_node/command/change_node_value.h"
#include "flow/math_node/event/node_value_change_event.h"
#include "flow/math_node/flow/value.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/component/properties/variant_property_manager.h>
#include <flow/document/document.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ---------------------- MathNodeDoubleEmitterProperties ------------------- */

MathNodeDoubleEmitterProperties::MathNodeDoubleEmitterProperties(
    QObject* parent)
    : NodeProperties(parent) {}

MathNodeDoubleEmitterProperties::~MathNodeDoubleEmitterProperties() = default;

void MathNodeDoubleEmitterProperties::init() {
  NodeProperties::init();

  auto prop = getObjectProperties();
  prop->createProperty(Property::Value, QMetaType::Double, tr("Value"));
}

void MathNodeDoubleEmitterProperties::onEvent(const ChangeEvent& event) {
  NodeProperties::onEvent(event);

  if (event.getType() == MathNodeDoubleEmittersChangeEvent::type) {
    auto& e = static_cast<const MathNodeDoubleEmittersChangeEvent&>(event);
    if (e.getNodes().contains(getNode())) update();
  }
}

void MathNodeDoubleEmitterProperties::updateObject() {
  NodeProperties::updateObject();

  auto prop = getObjectProperties();
  if (auto node = static_cast<MathNodeDoubleEmitter*>(getNode()); node) {
    prop->getPropertyById(Property::Value)->setValue(node->getValue());
  }
}

void MathNodeDoubleEmitterProperties::applyObject(size_t id,
                                                  const QVariant& value) {
  NodeProperties::applyObject(id, value);

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

}  // namespace flow