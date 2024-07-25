#ifndef MATH_NODE_EQUAL_H
#define MATH_NODE_EQUAL_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_MATH_NODE_API MathNodeEqual : public NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeEqual, NodeWithTwoParams)

 public:
  explicit MathNodeEqual();
  ~MathNodeEqual() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // MATH_NODE_EQUAL_H
