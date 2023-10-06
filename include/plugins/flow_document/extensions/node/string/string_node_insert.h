#ifndef STRING_NODE_INSERT_H
#define STRING_NODE_INSERT_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class STRING_NODE_API StringNodeInsert
    : public flow_document::NodeWithThreeParams {
  FLOW_OBJECT_CLASS(StringNodeInsert, flow_document::NodeWithThreeParams)

 public:
  explicit StringNodeInsert();
  ~StringNodeInsert() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // STRING_NODE_INSERT_H
