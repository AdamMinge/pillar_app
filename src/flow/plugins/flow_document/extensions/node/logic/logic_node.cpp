/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/logic_node.h"
/* ----------------------------------- LibFlow ------------------------------ */
#include <flow/libflow/node/base/boolean_node_data.h>
/* -------------------------------------------------------------------------- */

/* --------------------------- LogicNodeWithOneParam ------------------------ */

LogicNodeWithOneParam::LogicNodeWithOneParam()
{
  auto in_pin = std::make_unique<flow::node::Pin>(
    std::make_unique<flow::node::base::BooleanNodeData>(false), "A");

  auto out_pin = std::make_unique<flow::node::Pin>(
    std::make_unique<flow::node::base::BooleanNodeData>(false), "Q");

  insertPin(flow::node::Pin::Type::In, std::move(in_pin), 0);
  insertPin(flow::node::Pin::Type::Out, std::move(out_pin), 0);
}

LogicNodeWithOneParam::~LogicNodeWithOneParam() = default;

/* -------------------------- LogicNodeWithTwoParams ------------------------ */

LogicNodeWithTwoParams::LogicNodeWithTwoParams()
{
  auto in_pin = std::make_unique<flow::node::Pin>(
    std::make_unique<flow::node::base::BooleanNodeData>(false), "B");

  insertPin(flow::node::Pin::Type::In, std::move(in_pin), 1);
}

LogicNodeWithTwoParams::~LogicNodeWithTwoParams() = default;
