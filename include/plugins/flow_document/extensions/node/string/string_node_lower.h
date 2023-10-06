#ifndef STRING_NODE_LOWER_H
#define STRING_NODE_LOWER_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class STRING_NODE_API StringNodeLower : public flow_document::NodeWithOneParam {
  FLOW_OBJECT_CLASS(StringNodeLower, flow_document::NodeWithOneParam)

 public:
  explicit StringNodeLower();
  ~StringNodeLower() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // STRING_NODE_LOWER_H
