/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/flow/power.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Base = 0, Exponent = 1 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* -------------------------------- MathNodePower --------------------------- */

MathNodePower::MathNodePower() {
  setName(QObject::tr("POWER"));

  getPin(Pin::Type::In, PinIn::Base).setCaption("Base");
  getPin(Pin::Type::In, PinIn::Exponent).setCaption("Exponent");
}

MathNodePower::~MathNodePower() = default;

std::unique_ptr<Node> MathNodePower::clone() const {
  auto node = std::make_unique<MathNodePower>();
  node->init(this);
  return std::move(node);
}

void MathNodePower::compute() {
  const auto &base_pin = getPin(Pin::Type::In, PinIn::Base);
  const auto &exponent_pin = getPin(Pin::Type::In, PinIn::Exponent);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto base = base_pin.getData().toReal();
  const auto exponent = exponent_pin.getData().toReal();

  result_pin.setData(qPow(base, exponent));
}

}  // namespace flow