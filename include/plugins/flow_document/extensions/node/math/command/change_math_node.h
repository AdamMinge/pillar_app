#ifndef CHANGE_MATH_NODE_H
#define CHANGE_MATH_NODE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/command/change_value.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "flow/math_node_value.h"
/* -------------------------------------------------------------------------- */

/* ----------------------- SetMathNodeFloatEmitterValue --------------------- */

class MATH_NODE_API SetMathNodeFloatEmitterValue
    : public flow_document::ChangeValue<MathNodeFloatEmitter, float> {
 public:
  explicit SetMathNodeFloatEmitterValue(flow_document::FlowDocument* document,
                                        QList<MathNodeFloatEmitter*> nodes,
                                        float value,
                                        egnite::Command* parent = nullptr);
  ~SetMathNodeFloatEmitterValue() override;

 protected:
  [[nodiscard]] float getValue(const MathNodeFloatEmitter* node) const override;
  void setValue(MathNodeFloatEmitter* node, const float& value) override;
};

#endif  // CHANGE_MATH_NODE_H