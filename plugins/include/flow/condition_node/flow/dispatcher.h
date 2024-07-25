#ifndef FLOW_CONDITION_NODE_DISPATCHER_H
#define FLOW_CONDITION_NODE_DISPATCHER_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/condition_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_CONDITION_NODE_API ConditionNodeDispatcher : public Node {
  FLOW_OBJECT_CLASS(ConditionNodeDispatcher, Node)

 public:
  explicit ConditionNodeDispatcher();
  ~ConditionNodeDispatcher() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // FLOW_CONDITION_NODE_DISPATCHER_H
