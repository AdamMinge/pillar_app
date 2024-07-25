#ifndef FLOW_LOGIC_NODE_NOT_H
#define FLOW_LOGIC_NODE_NOT_H

/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_LOGIC_NODE_API LogicNodeNot : public NodeWithOneParam {
  FLOW_OBJECT_CLASS(LogicNodeNot, NodeWithOneParam)

 public:
  explicit LogicNodeNot();
  ~LogicNodeNot() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // FLOW_LOGIC_NODE_NOT_H
