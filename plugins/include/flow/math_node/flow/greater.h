#ifndef MATH_NODE_GREATER_H
#define MATH_NODE_GREATER_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_MATH_NODE_API MathNodeGreater : public NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeGreater, NodeWithTwoParams)

 public:
  explicit MathNodeGreater();
  ~MathNodeGreater() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // MATH_NODE_GREATER_H
