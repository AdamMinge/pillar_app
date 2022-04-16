#ifndef FLOW_LOGIC_NODE_DATA_H
#define FLOW_LOGIC_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include <flow/modules/node/node_data.h>
/* -------------------------------------------------------------------------- */

namespace node
{

  class NODE_API LogicNodeData : public ::node::NodeData
  {
  public:
    explicit LogicNodeData(bool value);
    ~LogicNodeData() override;

    void setValue(bool value);
    [[nodiscard]] bool getValue() const;

    void assign(const NodeData &data) override;

  private:
    bool m_value;
  };

}//namespace node

#endif//FLOW_LOGIC_NODE_DATA_H
