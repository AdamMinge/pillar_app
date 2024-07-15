#ifndef CONDITION_NODE_SWITCHER_H
#define CONDITION_NODE_SWITCHER_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class CONDITION_NODE_API ConditionNodeSwitcher
    : public flow_document::NodeWithThreeParams {
  FLOW_OBJECT_CLASS(ConditionNodeSwitcher, flow_document::NodeWithThreeParams)

 public:
  explicit ConditionNodeSwitcher();
  ~ConditionNodeSwitcher() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // CONDITION_NODE_SWITCHER_H
