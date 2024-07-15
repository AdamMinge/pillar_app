#ifndef MATH_NODE_SUBTRACTION_H
#define MATH_NODE_SUBTRACTION_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodeSubtraction
    : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeSubtraction, flow_document::NodeWithTwoParams)

 public:
  explicit MathNodeSubtraction();
  ~MathNodeSubtraction() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // MATH_NODE_SUBTRACTION_H
