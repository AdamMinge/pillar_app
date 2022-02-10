/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/logic_node_not.h"
#include "flow/plugins/node/logic/logic_node_data.h"
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  LogicNodeNot::LogicNodeNot() = default;

  LogicNodeNot::~LogicNodeNot() = default;

  void LogicNodeNot::compute()
  {
    auto &in_pin_0 = getPin(::node::Pin::Type::In, 0);
    auto &out_pin = getPin(::node::Pin::Type::Out, 0);

    auto value_A =
      dynamic_cast<const LogicNodeData &>(in_pin_0.getData()).getValue();

    const auto out_data = LogicNodeData(!value_A);
    out_pin.setData(out_data);
  }

}// namespace plugins::node::logic