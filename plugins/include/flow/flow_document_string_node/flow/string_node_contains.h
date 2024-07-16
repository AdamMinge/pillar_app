#ifndef STRING_NODE_CONTAINS_H
#define STRING_NODE_CONTAINS_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class STRING_NODE_API StringNodeContains
    : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(StringNodeContains, flow_document::NodeWithTwoParams)

 public:
  explicit StringNodeContains();
  ~StringNodeContains() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // STRING_NODE_CONTAINS_H
