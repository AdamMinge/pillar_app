#ifndef STRING_NODE_UPPER_H
#define STRING_NODE_UPPER_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class STRING_NODE_API StringNodeUpper : public flow_document::NodeWithOneParam {
  FLOW_OBJECT_CLASS(StringNodeUpper, flow_document::NodeWithOneParam)

 public:
  explicit StringNodeUpper();
  ~StringNodeUpper() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // STRING_NODE_UPPER_H
