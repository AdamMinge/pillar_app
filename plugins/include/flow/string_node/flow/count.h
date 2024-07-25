#ifndef STRING_NODE_COUNT_H
#define STRING_NODE_COUNT_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_STRING_NODE_API StringNodeCount : public NodeWithTwoParams {
  FLOW_OBJECT_CLASS(StringNodeCount, NodeWithTwoParams)

 public:
  explicit StringNodeCount();
  ~StringNodeCount() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // STRING_NODE_COUNT_H
