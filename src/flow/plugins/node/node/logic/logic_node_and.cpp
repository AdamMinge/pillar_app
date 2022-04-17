/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/logic_node_and.h"
/* ------------------------------------ Node -------------------------------- */
#include "flow/modules/node/base/boolean_node_data.h"
/* -------------------------------------------------------------------------- */

LogicNodeAnd::LogicNodeAnd() = default;

LogicNodeAnd::~LogicNodeAnd() = default;

void LogicNodeAnd::compute()
{
  auto &in_pin_0 = getPin(::node::Pin::Type::In, 0);
  auto &in_pin_1 = getPin(::node::Pin::Type::In, 1);
  auto &out_pin = getPin(::node::Pin::Type::Out, 0);

  auto value_A =
    dynamic_cast<const node::base::BooleanNodeData &>(in_pin_0.getData())
      .getValue();
  auto value_B =
    dynamic_cast<const node::base::BooleanNodeData &>(in_pin_1.getData())
      .getValue();

  const auto out_data = node::base::BooleanNodeData(value_A & value_B);
  out_pin.setData(out_data);
}
