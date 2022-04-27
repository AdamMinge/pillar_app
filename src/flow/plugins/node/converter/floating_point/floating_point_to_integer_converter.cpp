/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/floating_point_to_integer_converter.h"
#include "flow/libflow/node/base/floating_point_node_data.h"
#include "flow/libflow/node/base/integer_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::node::NodeData>
FloatingPointToIntegerConverter::convert(const flow::node::NodeData &data)
{
  auto &floating_point_data =
    dynamic_cast<const flow::node::base::FloatingPointNodeData &>(data);
  return std::make_unique<flow::node::base::IntegerNodeData>(
    static_cast<int>(floating_point_data.getValue()));
}
