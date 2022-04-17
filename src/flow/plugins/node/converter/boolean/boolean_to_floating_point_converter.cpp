/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/boolean/boolean_to_floating_point_converter.h"
#include "flow/modules/node/base/boolean_node_data.h"
#include "flow/modules/node/base/floating_point_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<node::NodeData>
BooleanToFloatingPointConverter::convert(const node::NodeData &data)
{
  auto &boolean_data = dynamic_cast<const node::base::BooleanNodeData &>(data);
  return std::make_unique<node::base::FloatingPointNodeData>(
    static_cast<float>(boolean_data.getValue()));
}
