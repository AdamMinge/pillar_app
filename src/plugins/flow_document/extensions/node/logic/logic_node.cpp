/* ----------------------------------- Local -------------------------------- */
#include "logic_node.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/node/base/boolean_node_data.h>
/* -------------------------------------------------------------------------- */

/* --------------------------- LogicNodeWithOneParam ------------------------ */

LogicNodeWithOneParam::LogicNodeWithOneParam() {
  auto in_pin = std::make_unique<flow_document::Pin>(
      std::make_unique<flow_document::BooleanNodeData>(false), "A");

  auto out_pin = std::make_unique<flow_document::Pin>(
      std::make_unique<flow_document::BooleanNodeData>(false), "Q");

  insertPin(flow_document::Pin::Type::In, std::move(in_pin), 0);
  insertPin(flow_document::Pin::Type::Out, std::move(out_pin), 0);
}

LogicNodeWithOneParam::~LogicNodeWithOneParam() = default;

/* -------------------------- LogicNodeWithTwoParams ------------------------ */

LogicNodeWithTwoParams::LogicNodeWithTwoParams() {
  auto in_pin = std::make_unique<flow_document::Pin>(
      std::make_unique<flow_document::BooleanNodeData>(false), "B");

  insertPin(flow_document::Pin::Type::In, std::move(in_pin), 1);
}

LogicNodeWithTwoParams::~LogicNodeWithTwoParams() = default;
