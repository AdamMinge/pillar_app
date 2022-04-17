#ifndef FLOW_LOGIC_NODE_NOT_H
#define FLOW_LOGIC_NODE_NOT_H

/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "logic_node.h"
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

#endif//FLOW_LOGIC_NODE_NOT_H
