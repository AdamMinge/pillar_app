#ifndef STRING_NODE_NOT_EQUAL_H
#define STRING_NODE_NOT_EQUAL_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class STRING_NODE_API StringNodeNotEqual
    : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(StringNodeNotEqual, flow_document::NodeWithTwoParams)

 public:
  explicit StringNodeNotEqual();
  ~StringNodeNotEqual() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // STRING_NODE_NOT_EQUAL_H
