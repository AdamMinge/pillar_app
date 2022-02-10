#ifndef FLOW_LOGIC_NODE_H
#define FLOW_LOGIC_NODE_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/export.h"
/* ------------------------------------ Api --------------------------------- */
#include <flow/modules/node/node.h>
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  class LOGIC_NODE_API LogicNodeWithOneParam : public ::node::Node
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

}// namespace plugins::node::logic

#endif//FLOW_LOGIC_NODE_H
