#ifndef MATH_NODE_GREATER_EQUAL_H
#define MATH_NODE_GREATER_EQUAL_H

/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_MATH_NODE_API MathNodeGreaterEqual : public NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeGreaterEqual, NodeWithTwoParams)

 public:
  explicit MathNodeGreaterEqual();
  ~MathNodeGreaterEqual() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // MATH_NODE_GREATER_EQUAL_H
