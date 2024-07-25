#ifndef STRING_NODE_MID_H
#define STRING_NODE_MID_H

/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_STRING_NODE_API StringNodeMid : public NodeWithThreeParams {
  FLOW_OBJECT_CLASS(StringNodeMid, NodeWithThreeParams)

 public:
  explicit StringNodeMid();
  ~StringNodeMid() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // STRING_NODE_MID_H
