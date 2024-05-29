#ifndef LOGIC_NODE_NAND_H
#define LOGIC_NODE_NAND_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeNAnd : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(LogicNodeNAnd, flow_document::NodeWithTwoParams)

 public:
  explicit LogicNodeNAnd();
  ~LogicNodeNAnd() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // LOGIC_NODE_NAND_H
