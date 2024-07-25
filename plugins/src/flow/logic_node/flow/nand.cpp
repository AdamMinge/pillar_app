/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/flow/nand.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Lhs = 0, Rhs = 1 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ------------------------------- LogicNodeNAnd ---------------------------- */

LogicNodeNAnd::LogicNodeNAnd() { setName(QObject::tr("NAND")); }

LogicNodeNAnd::~LogicNodeNAnd() = default;

std::unique_ptr<Node> LogicNodeNAnd::clone() const {
  auto node = std::make_unique<LogicNodeNAnd>();
  node->init(this);
  return std::move(node);
}

void LogicNodeNAnd::compute() {
  auto &lhs_pin = getPin(Pin::Type::In, PinIn::Lhs);
  auto &rhs_pin = getPin(Pin::Type::In, PinIn::Rhs);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto lhs = lhs_pin.getData().toBool();
  const auto rhs = rhs_pin.getData().toBool();

  result_pin.setData(!static_cast<bool>(lhs & rhs));
}

}  // namespace flow