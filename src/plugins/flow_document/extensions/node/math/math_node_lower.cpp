/* ----------------------------------- Local -------------------------------- */
#include "math_node_lower.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Lhs = 0, Rhs = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------- MathNodeLower ---------------------------- */

MathNodeLower::MathNodeLower() { setName(QObject::tr("LOWER")); }

MathNodeLower::~MathNodeLower() = default;

std::unique_ptr<flow_document::Node> MathNodeLower::clone() const {
  auto node = std::make_unique<MathNodeLower>();
  node->init(this);
  return std::move(node);
}

void MathNodeLower::compute() {
  auto &lhs_pin = getPin(flow_document::Pin::Type::In, Lhs);
  auto &rhs_pin = getPin(flow_document::Pin::Type::In, Rhs);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, Result);

  const auto lhs = lhs_pin.getData().toReal();
  const auto rhs = rhs_pin.getData().toReal();

  result_pin.setData(lhs < rhs);
}