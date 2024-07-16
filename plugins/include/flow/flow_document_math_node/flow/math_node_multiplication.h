#ifndef MATH_NODE_MULTIPLICATION_H
#define MATH_NODE_MULTIPLICATION_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodeMultiplication
    : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeMultiplication, flow_document::NodeWithTwoParams)

 public:
  explicit MathNodeMultiplication();
  ~MathNodeMultiplication() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // MATH_NODE_MULTIPLICATION_H
