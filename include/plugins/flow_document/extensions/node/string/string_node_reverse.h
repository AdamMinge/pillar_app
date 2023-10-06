#ifndef STRING_NODE_REVERSE_H
#define STRING_NODE_REVERSE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class STRING_NODE_API StringNodeReverse
    : public flow_document::NodeWithOneParam {
  FLOW_OBJECT_CLASS(StringNodeReverse, flow_document::NodeWithOneParam)

 public:
  explicit StringNodeReverse();
  ~StringNodeReverse() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // STRING_NODE_REVERSE_H
