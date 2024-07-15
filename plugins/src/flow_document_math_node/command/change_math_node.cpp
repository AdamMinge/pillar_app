/* ----------------------------------- Local -------------------------------- */
#include "command/change_math_node.h"

#include "event/math_node_change_event.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow_document.h>
/* -------------------------------------------------------------------------- */

/* ----------------------- SetMathNodeDoubleEmitterValue -------------------- */

SetMathNodeDoubleEmitterValue::SetMathNodeDoubleEmitterValue(
    flow_document::FlowDocument* document, QList<MathNodeDoubleEmitter*> nodes,
    double value, egnite::Command* parent)
    : ChangeValue<MathNodeDoubleEmitter, double>(
          QLatin1String("SetMathNodeDoubleEmitterValue"), document,
          std::move(nodes), value, parent) {
  const auto what = QObject::tr("Set Node(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Emiter Value");

  setText(QString("%1 %2").arg(what, action));
}

SetMathNodeDoubleEmitterValue::~SetMathNodeDoubleEmitterValue() = default;

double SetMathNodeDoubleEmitterValue::getValue(
    const MathNodeDoubleEmitter* node) const {
  return node->getValue();
}

void SetMathNodeDoubleEmitterValue::setValue(MathNodeDoubleEmitter* node,
                                             const double& value) {
  node->setValue(value);
  getDocument()->event(MathNodeDoubleEmittersChangeEvent(
      {node}, MathNodeDoubleEmittersChangeEvent::Property::Value));
}
