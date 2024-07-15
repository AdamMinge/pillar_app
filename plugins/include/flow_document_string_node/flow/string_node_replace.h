#ifndef STRING_NODE_REPLACE_H
#define STRING_NODE_REPLACE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class STRING_NODE_API StringNodeReplace
    : public flow_document::NodeWithThreeParams {
  FLOW_OBJECT_CLASS(StringNodeReplace, flow_document::NodeWithThreeParams)

 public:
  explicit StringNodeReplace();
  ~StringNodeReplace() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // STRING_NODE_REPLACE_H
