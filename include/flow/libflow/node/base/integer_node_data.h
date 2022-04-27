#ifndef FLOW_INTEGER_NODE_DATA_H
#define FLOW_INTEGER_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/node/node_data.h"
/* -------------------------------------------------------------------------- */

namespace flow::node::base
{

  class LIB_FLOW_API IntegerNodeData : public NodeData
  {
  public:
    explicit IntegerNodeData(int value);
    ~IntegerNodeData() override;

    void setValue(int value);
    [[nodiscard]] int getValue() const;

    void assign(const NodeData &data) override;

  private:
    int m_value;
  };

}// namespace flow::node::base

#endif//FLOW_INTEGER_NODE_DATA_H
