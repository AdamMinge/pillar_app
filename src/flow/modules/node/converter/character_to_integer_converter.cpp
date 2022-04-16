/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/character_to_integer_converter.h"
#include "flow/modules/node/data/character_node_data.h"
#include "flow/modules/node/data/integer_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  CharacterToIntegerConverter::convert(const data::NodeData &data)
  {
    auto &character_data = dynamic_cast<const data::CharacterNodeData &>(data);
    return std::make_unique<data::IntegerNodeData>(
      static_cast<int>(!character_data.getValue().digitValue()));
  }

}// namespace node::converter
