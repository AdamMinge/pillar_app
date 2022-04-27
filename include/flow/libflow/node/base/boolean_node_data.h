#ifndef FLOW_BOOLEAN_NODE_DATA_H
#define FLOW_BOOLEAN_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/node/node_data.h"
/* -------------------------------------------------------------------------- */

namespace flow::node::base
{

  class LIB_FLOW_API BooleanNodeData : public NodeData
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

}// namespace flow::node::base

#endif//FLOW_BOOLEAN_NODE_DATA_H
