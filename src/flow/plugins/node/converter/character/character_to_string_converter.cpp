/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/character/character_to_string_converter.h"
#include "flow/modules/node/base/character_node_data.h"
#include "flow/modules/node/base/string_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<node::NodeData>
CharacterToStringConverter::convert(const node::NodeData &data)
{
  auto &character_data =
    dynamic_cast<const node::base::CharacterNodeData &>(data);
  return std::make_unique<node::base::StringNodeData>(
    character_data.getValue());
}
