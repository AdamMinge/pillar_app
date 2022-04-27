/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/floating_point/floating_point_to_string_converter.h"
#include "flow/libflow/node/base/floating_point_node_data.h"
#include "flow/libflow/node/base/string_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::node::NodeData>
FloatingPointToStringConverter::convert(const flow::node::NodeData &data)
{
  auto &floating_point_data =
    dynamic_cast<const flow::node::base::FloatingPointNodeData &>(data);
  return std::make_unique<flow::node::base::StringNodeData>(
    QString("%1").arg(floating_point_data.getValue()));
}
