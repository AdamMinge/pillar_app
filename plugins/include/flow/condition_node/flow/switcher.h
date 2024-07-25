#ifndef FLOW_CONDITION_NODE_SWITCHER_H
#define FLOW_CONDITION_NODE_SWITCHER_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/condition_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_CONDITION_NODE_API ConditionNodeSwitcher
    : public NodeWithThreeParams {
  FLOW_OBJECT_CLASS(ConditionNodeSwitcher, NodeWithThreeParams)

 public:
  explicit ConditionNodeSwitcher();
  ~ConditionNodeSwitcher() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // FLOW_CONDITION_NODE_SWITCHER_H
