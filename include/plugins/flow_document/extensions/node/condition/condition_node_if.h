#ifndef CONDITION_NODE_IF_H
#define CONDITION_NODE_IF_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class CONDITION_NODE_API ConditionNodeIf : public flow_document::Node {
  FLOW_OBJECT_CLASS(ConditionNodeIf, flow_document::Node)

 public:
  explicit ConditionNodeIf();
  ~ConditionNodeIf() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // CONDITION_NODE_IF_H
