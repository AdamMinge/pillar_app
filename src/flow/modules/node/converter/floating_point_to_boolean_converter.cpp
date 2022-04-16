/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/floating_point_to_boolean_converter.h"
#include "flow/modules/node/data/boolean_node_data.h"
#include "flow/modules/node/data/floating_point_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  FloatingPointToBooleanConverter::convert(const data::NodeData &data)
  {
    auto &floating_point_data =
      dynamic_cast<const data::FloatingPointNodeData &>(data);
    return std::make_unique<data::BooleanNodeData>(
      static_cast<bool>(floating_point_data.getValue()));
  }

}// namespace node::converter
