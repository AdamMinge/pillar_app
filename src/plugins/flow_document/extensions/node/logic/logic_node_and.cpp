/* ----------------------------------- Local -------------------------------- */
#include "logic_node_and.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Lhs = 0, Rhs = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------- LogicNodeAnd ----------------------------- */

LogicNodeAnd::LogicNodeAnd() { setName(QObject::tr("AND")); }

LogicNodeAnd::~LogicNodeAnd() = default;

std::unique_ptr<flow_document::Node> LogicNodeAnd::clone() const {
  auto node = std::make_unique<LogicNodeAnd>();
  node->init(this);
  return std::move(node);
}

void LogicNodeAnd::compute() {
  auto &lhs_pin = getPin(flow_document::Pin::Type::In, PinIn::Lhs);
  auto &rhs_pin = getPin(flow_document::Pin::Type::In, PinIn::Rhs);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto lhs = lhs_pin.getData().toBool();
  const auto rhs = rhs_pin.getData().toBool();

  result_pin.setData(static_cast<bool>(lhs & rhs));
}
