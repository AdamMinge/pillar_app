/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/data/floating_point_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::data
{

  FloatingPointNodeData::FloatingPointNodeData(double value) : m_value(value) {}

  FloatingPointNodeData::~FloatingPointNodeData() = default;

  void FloatingPointNodeData::setValue(double value) { m_value = value; }

  double FloatingPointNodeData::getValue() const { return m_value; }

  void FloatingPointNodeData::assign(const NodeData &data)
  {
    auto &floating_point_node_data =
      dynamic_cast<const FloatingPointNodeData &>(data);
    setValue(floating_point_node_data.getValue());
  }

}// namespace node::data
