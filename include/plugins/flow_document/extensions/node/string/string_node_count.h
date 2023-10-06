#ifndef STRING_NODE_COUNT_H
#define STRING_NODE_COUNT_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class STRING_NODE_API StringNodeCount
    : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(StringNodeCount, flow_document::NodeWithTwoParams)

 public:
  explicit StringNodeCount();
  ~StringNodeCount() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // STRING_NODE_COUNT_H
