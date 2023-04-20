#ifndef PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_LOGIC_NODE_OR_H
#define PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_LOGIC_NODE_OR_H

/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "logic_node.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeOr : public LogicNodeWithTwoParams {
 public:
  explicit LogicNodeOr();
  ~LogicNodeOr() override;

 protected:
  void compute() override;
};

#endif  // PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_LOGIC_NODE_OR_H
