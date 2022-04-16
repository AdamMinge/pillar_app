/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/boolean_to_floating_point_converter.h"
#include "flow/modules/node/data/boolean_node_data.h"
#include "flow/modules/node/data/floating_point_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  BooleanToFloatingPointConverter::convert(const data::NodeData &data)
  {
    auto &boolean_data = dynamic_cast<const data::BooleanNodeData &>(data);
    return std::make_unique<data::FloatingPointNodeData>(
      static_cast<float>(boolean_data.getValue()));
  }

}// namespace node::converter
