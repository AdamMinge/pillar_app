#ifndef FLOW_LOGIC_NODE_AND_H
#define FLOW_LOGIC_NODE_AND_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_LOGIC_NODE_API LogicNodeAnd : public NodeWithTwoParams {
  FLOW_OBJECT_CLASS(LogicNodeAnd, NodeWithTwoParams)

 public:
  explicit LogicNodeAnd();
  ~LogicNodeAnd() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // FLOW_LOGIC_NODE_AND_H
