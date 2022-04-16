#ifndef FLOW_FLOATING_POINT_NODE_DATA_H
#define FLOW_FLOATING_POINT_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include <flow/modules/node/data/node_data.h>
/* -------------------------------------------------------------------------- */

namespace node::data
{

  class NODE_API FloatingPointNodeData : public NodeData
  {
  public:
    explicit FloatingPointNodeData(double value);
    ~FloatingPointNodeData() override;

    void setValue(double value);
    [[nodiscard]] double getValue() const;

    void assign(const NodeData &data) override;

  private:
    double m_value;
  };

}//namespace node::data

#endif//FLOW_FLOATING_POINT_NODE_DATA_H
