/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/integer_to_character_converter.h"
#include "flow/modules/node/data/character_node_data.h"
#include "flow/modules/node/data/integer_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  IntegerToCharacterConverter::convert(const data::NodeData &data)
  {
    auto &integer_point_data =
      dynamic_cast<const data::IntegerNodeData &>(data);
    return std::make_unique<data::CharacterNodeData>(
      QChar(integer_point_data.getValue()));
  }

}// namespace node::converter
