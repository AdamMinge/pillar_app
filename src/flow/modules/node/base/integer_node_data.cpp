/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/base/integer_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::base
{

  IntegerNodeData::IntegerNodeData(int value) : m_value(value) {}

  IntegerNodeData::~IntegerNodeData() = default;

  void IntegerNodeData::setValue(int value) { m_value = value; }

  int IntegerNodeData::getValue() const { return m_value; }

  void IntegerNodeData::assign(const NodeData &data)
  {
    auto &integer_node_data = dynamic_cast<const IntegerNodeData &>(data);
    setValue(integer_node_data.getValue());
  }

}// namespace node::base
