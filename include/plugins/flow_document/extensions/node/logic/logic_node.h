#ifndef LOGIC_NODE_H
#define LOGIC_NODE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/flow_node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeWithOneParam : public flow_document::FlowNode {
 public:
  explicit LogicNodeWithOneParam();
  ~LogicNodeWithOneParam() override;
};

class LOGIC_NODE_API LogicNodeWithTwoParams : public LogicNodeWithOneParam {
 public:
  explicit LogicNodeWithTwoParams();
  ~LogicNodeWithTwoParams() override;
};

#endif  // LOGIC_NODE_H
