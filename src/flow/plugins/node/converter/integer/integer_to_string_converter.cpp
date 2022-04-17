/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/integer_to_string_converter.h"
#include "flow/modules/node/base/integer_node_data.h"
#include "flow/modules/node/base/string_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<node::NodeData>
IntegerToStringConverter::convert(const node::NodeData &data)
{
  auto &integer_point_data =
    dynamic_cast<const node::base::IntegerNodeData &>(data);
  return std::make_unique<node::base::StringNodeData>(
    QString("%1").arg(integer_point_data.getValue()));
}
