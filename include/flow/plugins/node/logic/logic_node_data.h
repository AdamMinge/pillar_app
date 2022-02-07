#ifndef FLOW_LOGIC_NODE_DATA_H
#define FLOW_LOGIC_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/export.h"
/* ------------------------------------ Api --------------------------------- */
#include <flow/api/node/node_data.h>
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  class LOGIC_NODE_API LogicNodeData : public api::node::INodeData
  {
  public:
    explicit LogicNodeData(bool value);
    ~LogicNodeData() override;

    void setValue(bool value);
    [[nodiscard]] bool getValue() const;

    [[nodiscard]] QString getId() const override;
    [[nodiscard]] QString getName() const override;

  private:
    bool m_value;
  };

}// namespace plugins::node::logic

#endif//FLOW_LOGIC_NODE_DATA_H
