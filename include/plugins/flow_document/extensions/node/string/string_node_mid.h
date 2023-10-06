#ifndef STRING_NODE_MID_H
#define STRING_NODE_MID_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class STRING_NODE_API StringNodeMid
    : public flow_document::NodeWithThreeParams {
  FLOW_OBJECT_CLASS(StringNodeMid, flow_document::NodeWithThreeParams)

 public:
  explicit StringNodeMid();
  ~StringNodeMid() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // STRING_NODE_MID_H
