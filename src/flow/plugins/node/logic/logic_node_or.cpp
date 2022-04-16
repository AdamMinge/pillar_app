/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/logic_node_or.h"
#include "flow/plugins/node/logic/logic_node_data.h"
/* -------------------------------------------------------------------------- */

LogicNodeOr::LogicNodeOr() = default;

LogicNodeOr::~LogicNodeOr() = default;

void LogicNodeOr::compute()
{
  auto &in_pin_0 = getPin(::node::Pin::Type::In, 0);
  auto &in_pin_1 = getPin(::node::Pin::Type::In, 1);
  auto &out_pin = getPin(::node::Pin::Type::Out, 0);

  auto value_A =
    dynamic_cast<const LogicNodeData &>(in_pin_0.getData()).getValue();
  auto value_B =
    dynamic_cast<const LogicNodeData &>(in_pin_1.getData()).getValue();

  const auto out_data = LogicNodeData(value_A | value_B);
  out_pin.setData(out_data);
}
