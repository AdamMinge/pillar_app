/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/string_to_floating_point_converter.h"
#include "flow/modules/node/data/floating_point_node_data.h"
#include "flow/modules/node/data/string_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  StringToFloatingPoint::convert(const data::NodeData &data)
  {
    auto &string_point_data = dynamic_cast<const data::StringNodeData &>(data);
    return std::make_unique<data::FloatingPointNodeData>(
      string_point_data.getValue().toDouble());
  }

}// namespace node::converter
