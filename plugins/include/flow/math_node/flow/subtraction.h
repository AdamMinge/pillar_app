#ifndef MATH_NODE_SUBTRACTION_H
#define MATH_NODE_SUBTRACTION_H

/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_MATH_NODE_API MathNodeSubtraction : public NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeSubtraction, NodeWithTwoParams)

 public:
  explicit MathNodeSubtraction();
  ~MathNodeSubtraction() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // MATH_NODE_SUBTRACTION_H
