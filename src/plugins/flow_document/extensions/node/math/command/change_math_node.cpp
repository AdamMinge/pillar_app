/* ----------------------------------- Local -------------------------------- */
#include "command/change_math_node.h"

#include "event/math_node_change_event.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow_document.h>
/* -------------------------------------------------------------------------- */

/* ----------------------- SetMathNodeFloatEmitterValue --------------------- */

SetMathNodeFloatEmitterValue::SetMathNodeFloatEmitterValue(
    flow_document::FlowDocument* document, QList<MathNodeFloatEmitter*> nodes,
    float value, egnite::Command* parent)
    : ChangeValue<MathNodeFloatEmitter, float>(
          QLatin1String("SetMathNodeFloatEmitterValue"), document,
          std::move(nodes), value, parent) {
  const auto what = QObject::tr("Set Node(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Emiter Value");

  setText(QString("%1 %2").arg(what, action));
}

SetMathNodeFloatEmitterValue::~SetMathNodeFloatEmitterValue() = default;

float SetMathNodeFloatEmitterValue::getValue(
    const MathNodeFloatEmitter* node) const {
  return node->getValue();
}

void SetMathNodeFloatEmitterValue::setValue(MathNodeFloatEmitter* node,
                                            const float& value) {
  node->setValue(value);
  getDocument()->event(MathNodeFloatEmittersChangeEvent(
      {node}, MathNodeFloatEmittersChangeEvent::Property::Value));
}
