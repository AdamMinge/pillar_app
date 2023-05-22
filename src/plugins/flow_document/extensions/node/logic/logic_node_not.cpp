/* ----------------------------------- Local -------------------------------- */
#include "logic_node_not.h"
/* -------------------------------------------------------------------------- */

LogicNodeNot::LogicNodeNot() { setName(QObject::tr("NOT")); }

LogicNodeNot::~LogicNodeNot() = default;

std::unique_ptr<flow_document::Node> LogicNodeNot::clone() const {
  auto node = std::make_unique<LogicNodeNot>();
  node->init(this);
  return std::move(node);
}

void LogicNodeNot::compute() {
  auto &in_pin_0 = getPin(flow_document::Pin::Type::In, 0);
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);

  const auto value_A = in_pin_0.getData().toBool();

  out_pin.setData(!value_A);
}
