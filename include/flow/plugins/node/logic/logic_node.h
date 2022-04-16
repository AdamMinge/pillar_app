#ifndef FLOW_LOGIC_NODE_H
#define FLOW_LOGIC_NODE_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/export.h"
/* ------------------------------------ Api --------------------------------- */
#include <flow/modules/node/node.h>
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeWithOneParam : public ::node::Node
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

#endif//FLOW_LOGIC_NODE_H
