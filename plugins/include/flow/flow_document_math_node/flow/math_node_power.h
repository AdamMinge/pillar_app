#ifndef MATH_NODE_POWER_H
#define MATH_NODE_POWER_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodePower : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodePower, flow_document::NodeWithTwoParams)

 public:
  explicit MathNodePower();
  ~MathNodePower() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // MATH_NODE_POWER_H
