#ifndef FLOW_STRING_NODE_DATA_H
#define FLOW_STRING_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include <flow/modules/node/node_data.h>
/* -------------------------------------------------------------------------- */

namespace node::base
{

  class NODE_API StringNodeData : public NodeData
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

}//namespace node::base

#endif//FLOW_STRING_NODE_DATA_H
