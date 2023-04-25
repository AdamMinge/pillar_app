/* ----------------------------------- Local -------------------------------- */
#include "logic_node.h"
/* -------------------------------------------------------------------------- */

/* --------------------------- LogicNodeWithOneParam ------------------------ */

LogicNodeWithOneParam::LogicNodeWithOneParam() {
  auto in_pin = flow_document::FlowPin({}, "A");
  auto out_pin = flow_document::FlowPin({}, "Q");

  insertPin(flow_document::FlowPin::Type::In, std::move(in_pin), 0);
  insertPin(flow_document::FlowPin::Type::Out, std::move(out_pin), 0);
}

LogicNodeWithOneParam::~LogicNodeWithOneParam() = default;

/* -------------------------- LogicNodeWithTwoParams ------------------------ */

LogicNodeWithTwoParams::LogicNodeWithTwoParams() {
  auto in_pin = flow_document::FlowPin({}, "B");

  insertPin(flow_document::FlowPin::Type::In, std::move(in_pin), 1);
}

LogicNodeWithTwoParams::~LogicNodeWithTwoParams() = default;
