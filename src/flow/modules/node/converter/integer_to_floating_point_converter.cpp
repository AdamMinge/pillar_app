/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/integer_to_floating_point_converter.h"
#include "flow/modules/node/data/floating_point_node_data.h"
#include "flow/modules/node/data/integer_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  IntegerToFloatingPointConverter::convert(const data::NodeData &data)
  {
    auto &integer_point_data =
      dynamic_cast<const data::IntegerNodeData &>(data);
    return std::make_unique<data::FloatingPointNodeData>(
      static_cast<float>(integer_point_data.getValue()));
  }

}// namespace node::converter
