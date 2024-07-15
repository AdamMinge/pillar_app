#ifndef LOGIC_NODE_NOT_H
#define LOGIC_NODE_NOT_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeNot : public flow_document::NodeWithOneParam {
  FLOW_OBJECT_CLASS(LogicNodeNot, flow_document::NodeWithOneParam)

 public:
  explicit LogicNodeNot();
  ~LogicNodeNot() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // LOGIC_NODE_NOT_H
