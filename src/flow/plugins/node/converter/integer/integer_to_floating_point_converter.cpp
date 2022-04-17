/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/integer_to_floating_point_converter.h"
#include "flow/modules/node/base/floating_point_node_data.h"
#include "flow/modules/node/base/integer_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<node::NodeData>
IntegerToFloatingPointConverter::convert(const node::NodeData &data)
{
  auto &integer_point_data =
    dynamic_cast<const node::base::IntegerNodeData &>(data);
  return std::make_unique<node::base::FloatingPointNodeData>(
    static_cast<float>(integer_point_data.getValue()));
}
