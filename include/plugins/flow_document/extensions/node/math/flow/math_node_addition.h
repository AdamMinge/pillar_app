#ifndef MATH_NODE_ADDITION_H
#define MATH_NODE_ADDITION_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodeAddition : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeAddition, flow_document::NodeWithTwoParams)

 public:
  explicit MathNodeAddition();
  ~MathNodeAddition() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // MATH_NODE_ADDITION_H
