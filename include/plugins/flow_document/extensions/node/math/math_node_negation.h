#ifndef MATH_NODE_NEGATION_H
#define MATH_NODE_NEGATION_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodeNegation : public flow_document::NodeWithOneParam {
  FLOW_OBJECT_CLASS(MathNodeNegation, flow_document::NodeWithOneParam)

 public:
  explicit MathNodeNegation();
  ~MathNodeNegation() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // MATH_NODE_NEGATION_H
