#ifndef CONDITION_NODE_DISPATCHER_H
#define CONDITION_NODE_DISPATCHER_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class CONDITION_NODE_API ConditionNodeDispatcher : public flow_document::Node {
  FLOW_OBJECT_CLASS(ConditionNodeDispatcher, flow_document::Node)

 public:
  explicit ConditionNodeDispatcher();
  ~ConditionNodeDispatcher() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // CONDITION_NODE_DISPATCHER_H
