#ifndef STRING_NODE_REPLACE_H
#define STRING_NODE_REPLACE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_STRING_NODE_API StringNodeReplace : public NodeWithThreeParams {
  FLOW_OBJECT_CLASS(StringNodeReplace, NodeWithThreeParams)

 public:
  explicit StringNodeReplace();
  ~StringNodeReplace() override;

  [[nodiscard]] std::unique_ptr<Node> clone() const override;

 protected:
  void compute() override;
};

}  // namespace flow

#endif  // STRING_NODE_REPLACE_H
