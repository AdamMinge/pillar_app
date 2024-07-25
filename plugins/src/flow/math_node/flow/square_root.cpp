/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/flow/square_root.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ----------------------------- MathNodeSquareRoot ------------------------- */

MathNodeSquareRoot::MathNodeSquareRoot() {
  setName(QObject::tr("SQUARE_ROOT"));
}

MathNodeSquareRoot::~MathNodeSquareRoot() = default;

std::unique_ptr<Node> MathNodeSquareRoot::clone() const {
  auto node = std::make_unique<MathNodeSquareRoot>();
  node->init(this);
  return std::move(node);
}

void MathNodeSquareRoot::compute() {
  const auto &value_pin = getPin(Pin::Type::In, PinIn::Value);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toReal();

  result_pin.setData(qSqrt(value));
}

}  // namespace flow