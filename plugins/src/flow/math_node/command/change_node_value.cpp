/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/command/change_node_value.h"

#include "flow/math_node/event/node_value_change_event.h"
/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/document.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ----------------------- SetMathNodeDoubleEmitterValue -------------------- */

SetMathNodeDoubleEmitterValue::SetMathNodeDoubleEmitterValue(
    FlowDocument* document, QList<MathNodeDoubleEmitter*> nodes, double value,
    pillar::Command* parent)
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

}  // namespace flow