/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/flow/greater.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Lhs = 0, Rhs = 1 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ------------------------------ MathNodeGreater --------------------------- */

MathNodeGreater::MathNodeGreater() { setName(QObject::tr("GREATER")); }

MathNodeGreater::~MathNodeGreater() = default;

std::unique_ptr<Node> MathNodeGreater::clone() const {
  auto node = std::make_unique<MathNodeGreater>();
  node->init(this);
  return std::move(node);
}

void MathNodeGreater::compute() {
  auto &lhs_pin = getPin(Pin::Type::In, PinIn::Lhs);
  auto &rhs_pin = getPin(Pin::Type::In, PinIn::Rhs);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto lhs = lhs_pin.getData().toReal();
  const auto rhs = rhs_pin.getData().toReal();

  result_pin.setData(lhs > rhs);
}

}  // namespace flow