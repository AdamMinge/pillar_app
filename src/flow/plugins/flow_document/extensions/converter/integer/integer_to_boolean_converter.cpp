/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/integer_to_boolean_converter.h"
#include "flow/libflow/node/base/boolean_node_data.h"
#include "flow/libflow/node/base/integer_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::node::NodeData>
IntegerToBooleanConverter::convert(const flow::node::NodeData &data)
{
  auto &integer_point_data =
    dynamic_cast<const flow::node::base::IntegerNodeData &>(data);
  return std::make_unique<flow::node::base::BooleanNodeData>(
    static_cast<bool>(integer_point_data.getValue()));
}
