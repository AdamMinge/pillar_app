#ifndef FLOW_LOGIC_NODE_XOR_H
#define FLOW_LOGIC_NODE_XOR_H

/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_LOGIC_NODE_API LogicNodeXOr : public NodeWithTwoParams {
  FLOW_OBJECT_CLASS(LogicNodeXOr, NodeWithTwoParams)

 public:
  explicit LogicNodeXOr();
  ~LogicNodeXOr() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // FLOW_LOGIC_NODE_XOR_H
