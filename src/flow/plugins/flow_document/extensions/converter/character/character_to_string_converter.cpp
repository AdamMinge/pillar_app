/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/character/character_to_string_converter.h"
#include "flow/libflow/node/base/character_node_data.h"
#include "flow/libflow/node/base/string_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::node::NodeData>
CharacterToStringConverter::convert(const flow::node::NodeData &data)
{
  auto &character_data =
    dynamic_cast<const flow::node::base::CharacterNodeData &>(data);
  return std::make_unique<flow::node::base::StringNodeData>(
    character_data.getValue());
}
