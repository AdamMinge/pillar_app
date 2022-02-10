#ifndef FLOW_LOGIC_NODE_OR_H
#define FLOW_LOGIC_NODE_OR_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/export.h"
#include "flow/plugins/node/logic/logic_node.h"
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  class LOGIC_NODE_API LogicNodeOr : public LogicNodeWithTwoParams
  {
    Q_OBJECT

  public:
    explicit LogicNodeOr();
    ~LogicNodeOr() override;

    [[nodiscard]] QString getName() const override;

  protected:
    void compute() override;
  };

}// namespace plugins::node::logic

#endif//FLOW_LOGIC_NODE_OR_H
