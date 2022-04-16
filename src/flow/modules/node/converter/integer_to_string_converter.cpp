/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/integer_to_string_converter.h"
#include "flow/modules/node/data/integer_node_data.h"
#include "flow/modules/node/data/string_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  IntegerToStringConverter::convert(const data::NodeData &data)
  {
    auto &integer_point_data =
      dynamic_cast<const data::IntegerNodeData &>(data);
    return std::make_unique<data::StringNodeData>(
      QString("%1").arg(integer_point_data.getValue()));
  }

}// namespace node::converter
