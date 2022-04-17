/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/string/string_to_floating_point_converter.h"
#include "flow/modules/node/base/floating_point_node_data.h"
#include "flow/modules/node/base/string_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<node::NodeData>
StringToFloatingPoint::convert(const node::NodeData &data)
{
  auto &string_point_data =
    dynamic_cast<const node::base::StringNodeData &>(data);
  return std::make_unique<node::base::FloatingPointNodeData>(
    string_point_data.getValue().toDouble());
}
