/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/floating_point_to_string_converter.h"
#include "flow/modules/node/base/floating_point_node_data.h"
#include "flow/modules/node/base/string_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<node::NodeData>
FloatingPointToStringConverter::convert(const node::NodeData &data)
{
  auto &floating_point_data =
    dynamic_cast<const node::base::FloatingPointNodeData &>(data);
  return std::make_unique<node::base::StringNodeData>(
    QString("%1").arg(floating_point_data.getValue()));
}
