/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/component/properties/node_value_properties.h"

#include "flow/logic_node/command/change_node_value.h"
#include "flow/logic_node/event/node_value_change_event.h"
#include "flow/logic_node/flow/value.h"
/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/component/properties/variant_property_manager.h>
#include <flow/document/document.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ---------------------- LogicNodeBoolEmitterProperties -------------------- */

LogicNodeBoolEmitterProperties::LogicNodeBoolEmitterProperties(QObject* parent)
    : NodeProperties(parent) {}

LogicNodeBoolEmitterProperties::~LogicNodeBoolEmitterProperties() = default;

void LogicNodeBoolEmitterProperties::init() {
  NodeProperties::init();

  auto prop = getObjectProperties();
  prop->createProperty(Property::Value, QMetaType::Bool, tr("Value"));
}

void LogicNodeBoolEmitterProperties::onEvent(const ChangeEvent& event) {
  NodeProperties::onEvent(event);

  if (event.getType() == LogicNodeBoolEmittersChangeEvent::type) {
    auto& e = static_cast<const LogicNodeBoolEmittersChangeEvent&>(event);
    if (e.getNodes().contains(getNode())) update();
  }
}

void LogicNodeBoolEmitterProperties::updateObject() {
  NodeProperties::updateObject();

  auto prop = getObjectProperties();
  if (auto node = static_cast<LogicNodeBoolEmitter*>(getNode()); node) {
    prop->getPropertyById(Property::Value)->setValue(node->getValue());
  }
}

void LogicNodeBoolEmitterProperties::applyObject(size_t id,
                                                 const QVariant& value) {
  NodeProperties::applyObject(id, value);

  auto node = static_cast<LogicNodeBoolEmitter*>(getNode());

  switch (id) {
    case Property::Value: {
      auto boolean = value.toBool();
      if (node->getValue() != boolean) {
        getDocument()->getUndoStack()->push(
            new SetLogicNodeBoolEmitterValue(getDocument(), {node}, boolean));
      }

      break;
    }
  }
}

}  // namespace flow