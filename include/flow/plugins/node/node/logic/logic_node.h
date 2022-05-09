#ifndef PLUGIN_FLOW_LOGIC_NODE_H
#define PLUGIN_FLOW_LOGIC_NODE_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/node.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/export.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeWithOneParam : public flow::node::Node
{
public:
  explicit LogicNodeWithOneParam();
  ~LogicNodeWithOneParam() override;
};

class LOGIC_NODE_API LogicNodeWithTwoParams : public LogicNodeWithOneParam
{
public:
  explicit LogicNodeWithTwoParams();
  ~LogicNodeWithTwoParams() override;
};

#endif//PLUGIN_FLOW_LOGIC_NODE_H
