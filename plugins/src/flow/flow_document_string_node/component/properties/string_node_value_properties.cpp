/* ----------------------------------- Local -------------------------------- */
#include "component/properties/string_node_value_properties.h"

#include "command/change_string_node.h"
#include "event/string_node_change_event.h"
#include "flow/string_node_value.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/properties/variant_property_manager.h>
#include <flow_document/flow_document.h>
/* -------------------------------------------------------------------------- */

/* --------------------- StringNodeStringEmitterProperties ------------------ */

StringNodeStringEmitterProperties::StringNodeStringEmitterProperties(
    QObject* parent)
    : flow_document::NodeProperties(parent) {}

StringNodeStringEmitterProperties::~StringNodeStringEmitterProperties() =
    default;

void StringNodeStringEmitterProperties::init() {
  flow_document::NodeProperties::init();

  auto prop = getObjectProperties();
  prop->createProperty(Property::Value, QMetaType::QString, tr("Value"));
}

void StringNodeStringEmitterProperties::onEvent(
    const flow_document::ChangeEvent& event) {
  flow_document::NodeProperties::onEvent(event);

  if (event.getType() == StringNodeStringEmittersChangeEvent::type) {
    auto& e = static_cast<const StringNodeStringEmittersChangeEvent&>(event);
    if (e.getNodes().contains(getNode())) update();
  }
}

void StringNodeStringEmitterProperties::updateObject() {
  flow_document::NodeProperties::updateObject();

  auto prop = getObjectProperties();
  if (auto node = static_cast<StringNodeStringEmitter*>(getNode()); node) {
    prop->getPropertyById(Property::Value)->setValue(node->getValue());
  }
}

void StringNodeStringEmitterProperties::applyObject(size_t id,
                                                    const QVariant& value) {
  flow_document::NodeProperties::applyObject(id, value);

  auto node = static_cast<StringNodeStringEmitter*>(getNode());

  switch (id) {
    case Property::Value: {
      auto str = value.toString();
      if (node->getValue() != str) {
        getDocument()->getUndoStack()->push(
            new SetStringNodeStringEmitterValue(getDocument(), {node}, str));
      }

      break;
    }
  }
}