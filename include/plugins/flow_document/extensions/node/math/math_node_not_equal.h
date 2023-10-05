#ifndef MATH_NODE_NOT_EQUAL_H
#define MATH_NODE_NOT_EQUAL_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodeNotEqual : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeNotEqual, flow_document::NodeWithTwoParams)

 public:
  explicit MathNodeNotEqual();
  ~MathNodeNotEqual() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // MATH_NODE_NOT_EQUAL_H
