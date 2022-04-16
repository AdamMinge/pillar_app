/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/floating_point_to_string_converter.h"
#include "flow/modules/node/data/floating_point_node_data.h"
#include "flow/modules/node/data/string_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  FloatingPointToStringConverter::convert(const data::NodeData &data)
  {
    auto &floating_point_data =
      dynamic_cast<const data::FloatingPointNodeData &>(data);
    return std::make_unique<data::StringNodeData>(
      QString("%1").arg(floating_point_data.getValue()));
  }

}// namespace node::converter
