/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/flow/lower_equal.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Lhs = 0, Rhs = 1 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ---------------------------- MathNodeLowerEqual -------------------------- */

MathNodeLowerEqual::MathNodeLowerEqual() {
  setName(QObject::tr("LOWER EQUAL"));
}

MathNodeLowerEqual::~MathNodeLowerEqual() = default;

std::unique_ptr<Node> MathNodeLowerEqual::clone() const {
  auto node = std::make_unique<MathNodeLowerEqual>();
  node->init(this);
  return std::move(node);
}

void MathNodeLowerEqual::compute() {
  auto &lhs_pin = getPin(Pin::Type::In, PinIn::Lhs);
  auto &rhs_pin = getPin(Pin::Type::In, PinIn::Rhs);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto lhs = lhs_pin.getData().toReal();
  const auto rhs = rhs_pin.getData().toReal();

  result_pin.setData(lhs <= rhs);
}

}  // namespace flow