/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/string_to_integer_converter.h"
#include "flow/modules/node/data/integer_node_data.h"
#include "flow/modules/node/data/string_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  StringToIntegerConverter::convert(const data::NodeData &data)
  {
    auto &string_point_data = dynamic_cast<const data::StringNodeData &>(data);
    return std::make_unique<data::IntegerNodeData>(
      string_point_data.getValue().toInt());
  }

}// namespace node::converter
