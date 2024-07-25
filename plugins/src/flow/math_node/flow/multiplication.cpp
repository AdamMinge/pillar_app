/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/flow/multiplication.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Multiplier = 0, Multiplicand = 1 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* --------------------------- MathNodeMultiplication ----------------------- */

MathNodeMultiplication::MathNodeMultiplication() {
  setName(QObject::tr("MULTIPLICATION"));

  getPin(Pin::Type::In, PinIn::Multiplier).setCaption("Multiplier");
  getPin(Pin::Type::In, PinIn::Multiplicand).setCaption("Multiplicand");
}

MathNodeMultiplication::~MathNodeMultiplication() = default;

std::unique_ptr<Node> MathNodeMultiplication::clone() const {
  auto node = std::make_unique<MathNodeMultiplication>();
  node->init(this);
  return std::move(node);
}

void MathNodeMultiplication::compute() {
  const auto &multiplier_pin = getPin(Pin::Type::In, PinIn::Multiplier);
  const auto &multiplicand_pin = getPin(Pin::Type::In, PinIn::Multiplicand);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto multiplier = multiplier_pin.getData().toReal();
  const auto multiplicand = multiplicand_pin.getData().toReal();

  result_pin.setData(multiplier * multiplicand);
}

}  // namespace flow