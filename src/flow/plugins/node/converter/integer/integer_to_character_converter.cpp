/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/converter/integer/integer_to_character_converter.h"
#include "flow/modules/node/base/character_node_data.h"
#include "flow/modules/node/base/integer_node_data.h"
/* -------------------------------------------------------------------------- */

std::unique_ptr<node::NodeData>
IntegerToCharacterConverter::convert(const node::NodeData &data)
{
  auto &integer_point_data =
    dynamic_cast<const node::base::IntegerNodeData &>(data);
  return std::make_unique<node::base::CharacterNodeData>(
    QChar(integer_point_data.getValue()));
}
