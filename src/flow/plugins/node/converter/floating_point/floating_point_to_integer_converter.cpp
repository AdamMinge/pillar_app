/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/floating_point_to_integer_converter.h"
#include "flow/modules/node/base/floating_point_node_data.h"
#include "flow/modules/node/base/integer_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<node::NodeData>
FloatingPointToIntegerConverter::convert(const node::NodeData &data)
{
  auto &floating_point_data =
    dynamic_cast<const node::base::FloatingPointNodeData &>(data);
  return std::make_unique<node::base::IntegerNodeData>(
    static_cast<int>(floating_point_data.getValue()));
}
