#ifndef MATH_NODE_SQUARE_ROOT_H
#define MATH_NODE_SQUARE_ROOT_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodeSquareRoot
    : public flow_document::NodeWithOneParam {
  FLOW_OBJECT_CLASS(MathNodeSquareRoot, flow_document::NodeWithOneParam)

 public:
  explicit MathNodeSquareRoot();
  ~MathNodeSquareRoot() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // MATH_NODE_SQUARE_ROOT_H
