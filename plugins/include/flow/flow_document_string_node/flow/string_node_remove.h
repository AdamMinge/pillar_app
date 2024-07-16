#ifndef STRING_NODE_REMOVE_H
#define STRING_NODE_REMOVE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class STRING_NODE_API StringNodeRemove
    : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(StringNodeRemove, flow_document::NodeWithTwoParams)

 public:
  explicit StringNodeRemove();
  ~StringNodeRemove() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // STRING_NODE_REMOVE_H
