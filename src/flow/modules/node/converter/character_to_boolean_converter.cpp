/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/converter/character_to_boolean_converter.h"
#include "flow/modules/node/data/boolean_node_data.h"
#include "flow/modules/node/data/character_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::converter
{

  std::unique_ptr<data::NodeData>
  CharacterToBooleanConverter::convert(const data::NodeData &data)
  {
    auto &character_data = dynamic_cast<const data::CharacterNodeData &>(data);
    return std::make_unique<data::BooleanNodeData>(
      static_cast<bool>(!character_data.getValue().isNull()));
  }

}// namespace node::converter
