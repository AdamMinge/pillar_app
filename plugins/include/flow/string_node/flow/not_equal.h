#ifndef STRING_NODE_NOT_EQUAL_H
#define STRING_NODE_NOT_EQUAL_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_STRING_NODE_API StringNodeNotEqual : public NodeWithTwoParams {
  FLOW_OBJECT_CLASS(StringNodeNotEqual, NodeWithTwoParams)

 public:
  explicit StringNodeNotEqual();
  ~StringNodeNotEqual() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // STRING_NODE_NOT_EQUAL_H
