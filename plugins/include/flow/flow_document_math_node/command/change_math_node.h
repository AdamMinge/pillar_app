#ifndef CHANGE_MATH_NODE_H
#define CHANGE_MATH_NODE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/command/change_value.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "flow/math_node_value.h"
/* -------------------------------------------------------------------------- */

/* ----------------------- SetMathNodeDoubleEmitterValue -------------------- */

class MATH_NODE_API SetMathNodeDoubleEmitterValue
    : public flow_document::ChangeValue<MathNodeDoubleEmitter, double> {
 public:
  explicit SetMathNodeDoubleEmitterValue(flow_document::FlowDocument* document,
                                         QList<MathNodeDoubleEmitter*> nodes,
                                         double value,
                                         pillar::Command* parent = nullptr);
  ~SetMathNodeDoubleEmitterValue() override;

 protected:
  [[nodiscard]] double getValue(
      const MathNodeDoubleEmitter* node) const override;
  void setValue(MathNodeDoubleEmitter* node, const double& value) override;
};

#endif  // CHANGE_MATH_NODE_H