/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/flow/subtraction.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Minuend = 0, Subtrahend = 1 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* ----------------------------- MathNodeSubtraction ------------------------ */

MathNodeSubtraction::MathNodeSubtraction() {
  setName(QObject::tr("SUBTRACTION"));

  getPin(Pin::Type::In, PinIn::Minuend).setCaption("Minuend");
  getPin(Pin::Type::In, PinIn::Subtrahend).setCaption("Subtrahend");
}

MathNodeSubtraction::~MathNodeSubtraction() = default;

std::unique_ptr<Node> MathNodeSubtraction::clone() const {
  auto node = std::make_unique<MathNodeSubtraction>();
  node->init(this);
  return std::move(node);
}

void MathNodeSubtraction::compute() {
  const auto &minuend_pin = getPin(Pin::Type::In, PinIn::Minuend);
  const auto &subtrahend_pin = getPin(Pin::Type::In, PinIn::Subtrahend);
  auto &result_pin = getPin(Pin::Type::Out, PinOut::Result);

  const auto minuend = minuend_pin.getData().toReal();
  const auto subtrahend = subtrahend_pin.getData().toReal();

  result_pin.setData(minuend - subtrahend);
}

}  // namespace flow