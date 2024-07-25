/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/flow/negation.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ------------------------------ MathNodeNegation -------------------------- */

MathNodeNegation::MathNodeNegation() { setName(QObject::tr("NEGATION")); }

MathNodeNegation::~MathNodeNegation() = default;

std::unique_ptr<Node> MathNodeNegation::clone() const {
  auto node = std::make_unique<MathNodeNegation>();
  node->init(this);
  return std::move(node);
}

void MathNodeNegation::compute() {
  const auto &value_pin = getPin(Pin::Type::In, PinIn::Value);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toReal();

  result_pin.setData(-value);
}

}  // namespace flow