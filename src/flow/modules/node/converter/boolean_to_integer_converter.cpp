/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/boolean_to_integer_converter.h"
#include "flow/modules/node/data/boolean_node_data.h"
#include "flow/modules/node/data/integer_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  BooleanToIntegerConverter::convert(const data::NodeData &data)
  {
    auto &boolean_data = dynamic_cast<const data::BooleanNodeData &>(data);
    return std::make_unique<data::IntegerNodeData>(
      static_cast<int>(boolean_data.getValue()));
  }

}// namespace node::converter
