#ifndef PLUGIN_FLOW_LOGIC_NODE_NOT_H
#define PLUGIN_FLOW_LOGIC_NODE_NOT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/export.h"
#include "flow/plugins/node/node/logic/logic_node.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeNot : public LogicNodeWithOneParam
{
  Q_OBJECT

public:
  explicit LogicNodeNot();
  ~LogicNodeNot() override;

protected:
  void compute() override;
};

#endif//PLUGIN_FLOW_LOGIC_NODE_NOT_H
