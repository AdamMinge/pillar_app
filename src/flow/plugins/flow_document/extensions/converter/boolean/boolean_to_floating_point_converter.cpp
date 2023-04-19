/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/boolean/boolean_to_floating_point_converter.h"
#include "flow/libflow/node/base/boolean_node_data.h"
#include "flow/libflow/node/base/floating_point_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::node::NodeData>
BooleanToFloatingPointConverter::convert(const flow::node::NodeData &data)
{
  auto &boolean_data = dynamic_cast<const flow::node::base::BooleanNodeData &>(data);
  return std::make_unique<flow::node::base::FloatingPointNodeData>(
    static_cast<float>(boolean_data.getValue()));
}
