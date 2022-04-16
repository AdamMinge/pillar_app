/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/string_to_boolean_converter.h"
#include "flow/modules/node/data/boolean_node_data.h"
#include "flow/modules/node/data/string_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  StringToBooleanConverter::convert(const data::NodeData &data)
  {
    auto &string_point_data = dynamic_cast<const data::StringNodeData &>(data);
    return std::make_unique<data::BooleanNodeData>(
      string_point_data.getValue().isEmpty());
  }

}// namespace node::converter
