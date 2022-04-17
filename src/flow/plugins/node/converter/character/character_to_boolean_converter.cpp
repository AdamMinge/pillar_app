/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/character/character_to_boolean_converter.h"
#include "flow/modules/node/base/boolean_node_data.h"
#include "flow/modules/node/base/character_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<node::NodeData>
CharacterToBooleanConverter::convert(const node::NodeData &data)
{
  auto &character_data =
    dynamic_cast<const node::base::CharacterNodeData &>(data);
  return std::make_unique<node::base::BooleanNodeData>(
    static_cast<bool>(!character_data.getValue().isNull()));
}
