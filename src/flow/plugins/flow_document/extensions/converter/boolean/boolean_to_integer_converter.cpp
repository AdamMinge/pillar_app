/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/boolean/boolean_to_integer_converter.h"
#include "flow/libflow/node/base/boolean_node_data.h"
#include "flow/libflow/node/base/integer_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::node::NodeData>
BooleanToIntegerConverter::convert(const flow::node::NodeData &data)
{
  auto &boolean_data = dynamic_cast<const flow::node::base::BooleanNodeData &>(data);
  return std::make_unique<flow::node::base::IntegerNodeData>(
    static_cast<int>(boolean_data.getValue()));
}
