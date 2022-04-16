#ifndef FLOW_BOOLEAN_NODE_DATA_H
#define FLOW_BOOLEAN_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include <flow/modules/node/data/node_data.h>
/* -------------------------------------------------------------------------- */

namespace node::data
{

  class NODE_API BooleanNodeData : public NodeData
  {
  public:
    explicit BooleanNodeData(bool value);
    ~BooleanNodeData() override;

    void setValue(bool value);
    [[nodiscard]] bool getValue() const;

    void assign(const NodeData &data) override;

  private:
    bool m_value;
  };

}//namespace node::data

#endif//FLOW_BOOLEAN_NODE_DATA_H
