#ifndef FLOW_LOGIC_NODE_DATA_H
#define FLOW_LOGIC_NODE_DATA_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/export.h"
/* ------------------------------------ Node -------------------------------- */
#include <flow/modules/node/node_data.h>
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeData : public ::node::NodeData
{
public:
  explicit LogicNodeData(bool value);
  ~LogicNodeData() override;

  void setValue(bool value);
  [[nodiscard]] bool getValue() const;

  void assign(const NodeData &data) override;

private:
  bool m_value;
};

#endif//FLOW_LOGIC_NODE_DATA_H
