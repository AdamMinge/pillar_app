#ifndef FLOW_CHARACTER_NODE_DATA_H
#define FLOW_CHARACTER_NODE_DATA_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QChar>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/node/node_data.h"
/* -------------------------------------------------------------------------- */

namespace flow::node::base
{

  class LIB_FLOW_API CharacterNodeData : public NodeData
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

}// namespace flow::node::base

#endif//FLOW_CHARACTER_NODE_DATA_H
