/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node_or.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Lhs = 0, Rhs = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------- LogicNodeOr ------------------------------ */

LogicNodeOr::LogicNodeOr() { setName(QObject::tr("OR")); }

LogicNodeOr::~LogicNodeOr() = default;

std::unique_ptr<flow_document::Node> LogicNodeOr::clone() const {
  auto node = std::make_unique<LogicNodeOr>();
  node->init(this);
  return std::move(node);
}

void LogicNodeOr::compute() {
  auto &lhs_pin = getPin(flow_document::Pin::Type::In, PinIn::Lhs);
  auto &rhs_pin = getPin(flow_document::Pin::Type::In, PinIn::Rhs);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto lhs = lhs_pin.getData().toBool();
  const auto rhs = rhs_pin.getData().toBool();

  result_pin.setData(static_cast<bool>(lhs | rhs));
}
