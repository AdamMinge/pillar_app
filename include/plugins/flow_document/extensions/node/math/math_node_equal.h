#ifndef MATH_NODE_EQUAL_H
#define MATH_NODE_EQUAL_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodeEqual : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeEqual, flow_document::NodeWithTwoParams)

 public:
  explicit MathNodeEqual();
  ~MathNodeEqual() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // MATH_NODE_EQUAL_H
