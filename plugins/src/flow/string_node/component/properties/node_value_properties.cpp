/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/component/properties/node_value_properties.h"

#include "flow/string_node/command/change_node_value.h"
#include "flow/string_node/event/node_value_change_event.h"
#include "flow/string_node/flow/value.h"
/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/component/properties/variant_property_manager.h>
#include <flow/document/document.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* --------------------- StringNodeStringEmitterProperties ------------------ */

StringNodeStringEmitterProperties::StringNodeStringEmitterProperties(
    QObject* parent)
    : NodeProperties(parent) {}

StringNodeStringEmitterProperties::~StringNodeStringEmitterProperties() =
    default;

void StringNodeStringEmitterProperties::init() {
  NodeProperties::init();

  auto prop = getObjectProperties();
  prop->createProperty(Property::Value, QMetaType::QString, tr("Value"));
}

void StringNodeStringEmitterProperties::onEvent(const ChangeEvent& event) {
  NodeProperties::onEvent(event);

  if (event.getType() == StringNodeStringEmittersChangeEvent::type) {
    auto& e = static_cast<const StringNodeStringEmittersChangeEvent&>(event);
    if (e.getNodes().contains(getNode())) update();
  }
}

void StringNodeStringEmitterProperties::updateObject() {
  NodeProperties::updateObject();

  auto prop = getObjectProperties();
  if (auto node = static_cast<StringNodeStringEmitter*>(getNode()); node) {
    prop->getPropertyById(Property::Value)->setValue(node->getValue());
  }
}

void StringNodeStringEmitterProperties::applyObject(size_t id,
                                                    const QVariant& value) {
  NodeProperties::applyObject(id, value);

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

}  // namespace flow