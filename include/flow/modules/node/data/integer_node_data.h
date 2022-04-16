#ifndef FLOW_INTEGER_NODE_DATA_H
#define FLOW_INTEGER_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include <flow/modules/node/data/node_data.h>
/* -------------------------------------------------------------------------- */

namespace node::data
{

  class NODE_API IntegerNodeData : public NodeData
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

}//namespace node::data

#endif//FLOW_INTEGER_NODE_DATA_H
