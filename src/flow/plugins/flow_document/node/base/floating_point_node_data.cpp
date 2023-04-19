/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/node/base/floating_point_node_data.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

FloatingPointNodeData::FloatingPointNodeData(double value) : m_value(value) {}

FloatingPointNodeData::~FloatingPointNodeData() = default;

void FloatingPointNodeData::setValue(double value) { m_value = value; }

double FloatingPointNodeData::getValue() const { return m_value; }

void FloatingPointNodeData::assign(const NodeData &data) {
  auto &floating_point_node_data =
      dynamic_cast<const FloatingPointNodeData &>(data);
  setValue(floating_point_node_data.getValue());
}

}  // namespace plugin::flow_document