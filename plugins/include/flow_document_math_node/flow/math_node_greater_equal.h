#ifndef MATH_NODE_GREATER_EQUAL_H
#define MATH_NODE_GREATER_EQUAL_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodeGreaterEqual
    : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeGreaterEqual, flow_document::NodeWithTwoParams)

 public:
  explicit MathNodeGreaterEqual();
  ~MathNodeGreaterEqual() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // MATH_NODE_GREATER_EQUAL_H
