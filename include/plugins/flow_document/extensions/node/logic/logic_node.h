#ifndef PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_LOGIC_NODE_H
#define PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_LOGIC_NODE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/node/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeWithOneParam : public flow_document::Node {
 public:
  explicit LogicNodeWithOneParam();
  ~LogicNodeWithOneParam() override;
};

class LOGIC_NODE_API LogicNodeWithTwoParams : public LogicNodeWithOneParam {
 public:
  explicit LogicNodeWithTwoParams();
  ~LogicNodeWithTwoParams() override;
};

#endif  // PLUGIN_FLOW_DOCUMENT_EXTENSION_NODE_LOGIC_LOGIC_NODE_H
