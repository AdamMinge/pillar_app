/* ----------------------------------- Local -------------------------------- */
#include "command/change_logic_node.h"

#include "event/logic_node_change_event.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow_document.h>
/* -------------------------------------------------------------------------- */

/* ----------------------- SetLogicNodeBoolEmitterValue --------------------- */

SetLogicNodeBoolEmitterValue::SetLogicNodeBoolEmitterValue(
    flow_document::FlowDocument* document, QList<LogicNodeBoolEmitter*> nodes,
    bool value, pillar::Command* parent)
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
