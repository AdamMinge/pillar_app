/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/character_to_string_converter.h"
#include "flow/modules/node/data/character_node_data.h"
#include "flow/modules/node/data/string_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  CharacterToStringConverter::convert(const data::NodeData &data)
  {
    auto &character_data = dynamic_cast<const data::CharacterNodeData &>(data);
    return std::make_unique<data::StringNodeData>(character_data.getValue());
  }

}// namespace node::converter
