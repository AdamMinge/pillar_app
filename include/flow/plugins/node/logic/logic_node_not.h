#ifndef FLOW_LOGIC_NODE_NOT_H
#define FLOW_LOGIC_NODE_NOT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/export.h"
#include "flow/plugins/node/logic/logic_node.h"
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  class LOGIC_NODE_API LogicNodeNot : public LogicNodeWithOneParam
  {
  public:
    explicit LogicNodeNot();
    ~LogicNodeNot() override;

  protected:
    void compute() override;
  };

}// namespace plugins::node::logic

#endif//FLOW_LOGIC_NODE_NOT_H
