#ifndef FLOW_LOGIC_NODE_NAND_H
#define FLOW_LOGIC_NODE_NAND_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_LOGIC_NODE_API LogicNodeNAnd : public NodeWithTwoParams {
  FLOW_OBJECT_CLASS(LogicNodeNAnd, NodeWithTwoParams)

 public:
  explicit LogicNodeNAnd();
  ~LogicNodeNAnd() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // FLOW_LOGIC_NODE_NAND_H
