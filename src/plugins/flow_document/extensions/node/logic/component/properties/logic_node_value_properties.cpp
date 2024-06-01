/* ----------------------------------- Local -------------------------------- */
#include "component/properties/logic_node_value_properties.h"

#include "command/change_logic_node.h"
#include "event/logic_node_change_event.h"
#include "flow/logic_node_value.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/properties/variant_property_manager.h>
#include <flow_document/flow_document.h>
/* -------------------------------------------------------------------------- */

/* ---------------------- LogicNodeBoolEmitterProperties -------------------- */

LogicNodeBoolEmitterProperties::LogicNodeBoolEmitterProperties(QObject* parent)
    : flow_document::NodeProperties(parent) {}

LogicNodeBoolEmitterProperties::~LogicNodeBoolEmitterProperties() = default;

void LogicNodeBoolEmitterProperties::init() {
  flow_document::NodeProperties::init();

  auto prop = getObjectProperties();
  prop->createProperty(Property::Value, QMetaType::Bool, tr("Value"));
}

void LogicNodeBoolEmitterProperties::onEvent(
    const flow_document::ChangeEvent& event) {
  flow_document::NodeProperties::onEvent(event);

  if (event.getType() == LogicNodeBoolEmittersChangeEvent::type) {
    auto& e = static_cast<const LogicNodeBoolEmittersChangeEvent&>(event);
    if (e.getNodes().contains(getNode())) update();
  }
}

void LogicNodeBoolEmitterProperties::updateObject() {
  flow_document::NodeProperties::updateObject();

  auto prop = getObjectProperties();
  if (auto node = static_cast<LogicNodeBoolEmitter*>(getNode()); node) {
    prop->getPropertyById(Property::Value)->setValue(node->getValue());
  }
}

void LogicNodeBoolEmitterProperties::applyObject(size_t id,
                                                 const QVariant& value) {
  flow_document::NodeProperties::applyObject(id, value);

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