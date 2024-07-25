#ifndef MATH_NODE_LOWER_H
#define MATH_NODE_LOWER_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_MATH_NODE_API MathNodeLower : public NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeLower, NodeWithTwoParams)

 public:
  explicit MathNodeLower();
  ~MathNodeLower() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // MATH_NODE_LOWER_H
