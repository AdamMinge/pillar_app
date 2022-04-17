/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/boolean/boolean_to_integer_converter.h"
#include "flow/modules/node/base/boolean_node_data.h"
#include "flow/modules/node/base/integer_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<node::NodeData>
BooleanToIntegerConverter::convert(const node::NodeData &data)
{
  auto &boolean_data = dynamic_cast<const node::base::BooleanNodeData &>(data);
  return std::make_unique<node::base::IntegerNodeData>(
    static_cast<int>(boolean_data.getValue()));
}
