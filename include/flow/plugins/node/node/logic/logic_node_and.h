#ifndef FLOW_LOGIC_NODE_AND_H
#define FLOW_LOGIC_NODE_AND_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/export.h"
#include "flow/plugins/node/node/logic/logic_node.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeAnd : public LogicNodeWithTwoParams
{
  Q_OBJECT

public:
  explicit LogicNodeAnd();
  ~LogicNodeAnd() override;

protected:
  void compute() override;
};

#endif//FLOW_LOGIC_NODE_AND_H
