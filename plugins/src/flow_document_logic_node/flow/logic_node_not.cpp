/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node_not.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

/* -------------------------------- LogicNodeNot ---------------------------- */

LogicNodeNot::LogicNodeNot() { setName(QObject::tr("NOT")); }

LogicNodeNot::~LogicNodeNot() = default;

std::unique_ptr<flow_document::Node> LogicNodeNot::clone() const {
  auto node = std::make_unique<LogicNodeNot>();
  node->init(this);
  return std::move(node);
}

void LogicNodeNot::compute() {
  auto &value_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toBool();

  result_pin.setData(!value);
}
