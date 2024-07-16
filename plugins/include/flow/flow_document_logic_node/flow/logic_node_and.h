#ifndef LOGIC_NODE_AND_H
#define LOGIC_NODE_AND_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeAnd : public flow_document::NodeWithTwoParams {
  FLOW_OBJECT_CLASS(LogicNodeAnd, flow_document::NodeWithTwoParams)

 public:
  explicit LogicNodeAnd();
  ~LogicNodeAnd() override;

  [[nodiscard]] std::unique_ptr<flow_document::Node> clone() const override;

 protected:
  void compute() override;
};

#endif  // LOGIC_NODE_AND_H
