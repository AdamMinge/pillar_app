#ifndef FLOW_CHARACTER_NODE_DATA_H
#define FLOW_CHARACTER_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include <flow/modules/node/data/node_data.h>
/* -------------------------------------------------------------------------- */

namespace node::data
{

  class NODE_API CharacterNodeData : public NodeData
  {
  public:
    explicit CharacterNodeData(QChar value);
    ~CharacterNodeData() override;

    void setValue(QChar value);
    [[nodiscard]] QChar getValue() const;

    void assign(const NodeData &data) override;

  private:
    QChar m_value;
  };

}//namespace node::data

#endif//FLOW_CHARACTER_NODE_DATA_H
