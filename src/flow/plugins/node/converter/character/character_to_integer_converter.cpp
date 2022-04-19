/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/character/character_to_integer_converter.h"
#include "flow/libflow/node/base/character_node_data.h"
#include "flow/libflow/node/base/integer_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<flow::node::NodeData>
CharacterToIntegerConverter::convert(const flow::node::NodeData &data)
{
  auto &character_data =
    dynamic_cast<const flow::node::base::CharacterNodeData &>(data);
  return std::make_unique<flow::node::base::IntegerNodeData>(
    static_cast<int>(!character_data.getValue().digitValue()));
}
