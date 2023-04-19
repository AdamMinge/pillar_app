/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/string/string_to_boolean_converter.h"
#include "flow/libflow/node/base/boolean_node_data.h"
#include "flow/libflow/node/base/string_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::node::NodeData>
StringToBooleanConverter::convert(const flow::node::NodeData &data)
{
  auto &string_point_data =
    dynamic_cast<const flow::node::base::StringNodeData &>(data);
  return std::make_unique<flow::node::base::BooleanNodeData>(
    string_point_data.getValue().isEmpty());
}
