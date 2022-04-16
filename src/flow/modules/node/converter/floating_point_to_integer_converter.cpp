/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/floating_point_to_integer_converter.h"
#include "flow/modules/node/data/floating_point_node_data.h"
#include "flow/modules/node/data/integer_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  FloatingPointToIntegerConverter::convert(const data::NodeData &data)
  {
    auto &floating_point_data =
      dynamic_cast<const data::FloatingPointNodeData &>(data);
    return std::make_unique<data::IntegerNodeData>(
      static_cast<int>(floating_point_data.getValue()));
  }

}// namespace node::converter
