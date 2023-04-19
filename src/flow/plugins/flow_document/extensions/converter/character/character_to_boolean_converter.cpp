/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/character/character_to_boolean_converter.h"
#include "flow/libflow/node/base/boolean_node_data.h"
#include "flow/libflow/node/base/character_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::node::NodeData>
CharacterToBooleanConverter::convert(const flow::node::NodeData &data)
{
  auto &character_data =
    dynamic_cast<const flow::node::base::CharacterNodeData &>(data);
  return std::make_unique<flow::node::base::BooleanNodeData>(
    static_cast<bool>(!character_data.getValue().isNull()));
}
