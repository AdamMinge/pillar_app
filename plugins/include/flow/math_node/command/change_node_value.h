#ifndef CHANGE_MATH_NODE_H
#define CHANGE_MATH_NODE_H

/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/command/change_value.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/export.h"
#include "flow/math_node/flow/value.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ----------------------- SetMathNodeDoubleEmitterValue -------------------- */

class LIB_FLOW_MATH_NODE_API SetMathNodeDoubleEmitterValue
    : public ChangeValue<MathNodeDoubleEmitter, double> {
 public:
  explicit SetMathNodeDoubleEmitterValue(FlowDocument* document,
                                         QList<MathNodeDoubleEmitter*> nodes,
                                         double value,
                                         pillar::Command* parent = nullptr);
  ~SetMathNodeDoubleEmitterValue() override;

 protected:
  [[nodiscard]] double getValue(
      const MathNodeDoubleEmitter* node) const override;
  void setValue(MathNodeDoubleEmitter* node, const double& value) override;
};

}  // namespace flow

#endif  // CHANGE_MATH_NODE_H