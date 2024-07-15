#ifndef MATH_NODE_GREATER_H
#define MATH_NODE_GREATER_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodeGreater : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(MathNodeGreater, flow_document::NodeWithTwoParams)

 public:
  explicit MathNodeGreater();
  ~MathNodeGreater() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // MATH_NODE_GREATER_H
