#ifndef LOGIC_NODE_OR_H
#define LOGIC_NODE_OR_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeOr : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(LogicNodeOr, flow_document::NodeWithTwoParams)

 public:
  explicit LogicNodeOr();
  ~LogicNodeOr() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // LOGIC_NODE_OR_H
