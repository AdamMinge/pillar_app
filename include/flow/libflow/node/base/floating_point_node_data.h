#ifndef FLOW_FLOATING_POINT_NODE_DATA_H
#define FLOW_FLOATING_POINT_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/node/node_data.h"
/* -------------------------------------------------------------------------- */

namespace flow::node::base
{

  class LIB_FLOW_API FloatingPointNodeData : public NodeData
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

}// namespace flow::node::base

#endif//FLOW_FLOATING_POINT_NODE_DATA_H
