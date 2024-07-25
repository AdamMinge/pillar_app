/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/command/change_node_value.h"

#include "flow/logic_node/event/node_value_change_event.h"
/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/document.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ----------------------- SetLogicNodeBoolEmitterValue --------------------- */

SetLogicNodeBoolEmitterValue::SetLogicNodeBoolEmitterValue(
    FlowDocument* document, QList<LogicNodeBoolEmitter*> nodes, bool value,
    pillar::Command* parent)
    : ChangeValue<LogicNodeBoolEmitter, bool>(
          QLatin1String("SetLogicNodeBoolEmitterValue"), document,
          std::move(nodes), value, parent) {
  const auto what = QObject::tr("Set Node(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Emiter Value");

  setText(QString("%1 %2").arg(what, action));
}

SetLogicNodeBoolEmitterValue::~SetLogicNodeBoolEmitterValue() = default;

bool SetLogicNodeBoolEmitterValue::getValue(
    const LogicNodeBoolEmitter* node) const {
  return node->getValue();
}

void SetLogicNodeBoolEmitterValue::setValue(LogicNodeBoolEmitter* node,
                                            const bool& value) {
  node->setValue(value);
  getDocument()->event(LogicNodeBoolEmittersChangeEvent(
      {node}, LogicNodeBoolEmittersChangeEvent::Property::Value));
}

}  // namespace flow