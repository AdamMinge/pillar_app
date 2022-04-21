#ifndef PLUGIN_FLOW_LOGIC_NODE_H
#define PLUGIN_FLOW_LOGIC_NODE_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/node.h>
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeWithOneParam : public flow::node::Node
{
  Q_OBJECT

public:
  explicit LogicNodeWithOneParam();
  ~LogicNodeWithOneParam() override;
};

class LOGIC_NODE_API LogicNodeWithTwoParams : public LogicNodeWithOneParam
{
  Q_OBJECT

public:
  explicit LogicNodeWithTwoParams();
  ~LogicNodeWithTwoParams() override;
};

#endif//PLUGIN_FLOW_LOGIC_NODE_H
