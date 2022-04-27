#ifndef FLOW_STRING_NODE_DATA_H
#define FLOW_STRING_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/node/node_data.h"
/* -------------------------------------------------------------------------- */

namespace flow::node::base
{

  class LIB_FLOW_API StringNodeData : public NodeData
  {
  public:
    explicit StringNodeData(QString value);
    ~StringNodeData() override;

    void setValue(QString value);
    [[nodiscard]] QString getValue() const;

    void assign(const NodeData &data) override;

  private:
    QString m_value;
  };

}// namespace flow::node::base

#endif//FLOW_STRING_NODE_DATA_H
