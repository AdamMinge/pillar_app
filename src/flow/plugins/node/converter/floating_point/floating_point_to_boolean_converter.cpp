/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/floating_point_to_boolean_converter.h"
#include "flow/modules/node/base/boolean_node_data.h"
#include "flow/modules/node/base/floating_point_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<node::NodeData>
FloatingPointToBooleanConverter::convert(const node::NodeData &data)
{
  auto &floating_point_data =
    dynamic_cast<const node::base::FloatingPointNodeData &>(data);
  return std::make_unique<node::base::BooleanNodeData>(
    static_cast<bool>(floating_point_data.getValue()));
}
