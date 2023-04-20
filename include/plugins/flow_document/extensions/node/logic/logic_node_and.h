#ifndef PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_LOGIC_NODE_AND_H
#define PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_LOGIC_NODE_AND_H

/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "logic_node.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeAnd : public LogicNodeWithTwoParams {
 public:
  explicit LogicNodeAnd();
  ~LogicNodeAnd() override;

 protected:
  void compute() override;
};

#endif  // PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_LOGIC_NODE_AND_H
