/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/flow/not.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* -------------------------------- LogicNodeNot ---------------------------- */

LogicNodeNot::LogicNodeNot() { setName(QObject::tr("NOT")); }

LogicNodeNot::~LogicNodeNot() = default;

std::unique_ptr<Node> LogicNodeNot::clone() const {
  auto node = std::make_unique<LogicNodeNot>();
  node->init(this);
  return std::move(node);
}

void LogicNodeNot::compute() {
  auto &value_pin = getPin(Pin::Type::In, PinIn::Value);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toBool();

  result_pin.setData(!value);
}

}  // namespace flow