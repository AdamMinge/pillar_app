/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/floating_point_to_boolean_converter.h"
#include "flow/libflow/node/base/boolean_node_data.h"
#include "flow/libflow/node/base/floating_point_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::node::NodeData>
FloatingPointToBooleanConverter::convert(const flow::node::NodeData &data)
{
  auto &floating_point_data =
    dynamic_cast<const flow::node::base::FloatingPointNodeData &>(data);
  return std::make_unique<flow::node::base::BooleanNodeData>(
    static_cast<bool>(floating_point_data.getValue()));
}
