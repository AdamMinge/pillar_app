/* ----------------------------------- Local -------------------------------- */
#include "math_node_square_root.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

/* ----------------------------- MathNodeSquareRoot ------------------------- */

MathNodeSquareRoot::MathNodeSquareRoot() {
  setName(QObject::tr("SQUARE_ROOT"));
}

MathNodeSquareRoot::~MathNodeSquareRoot() = default;

std::unique_ptr<flow_document::Node> MathNodeSquareRoot::clone() const {
  auto node = std::make_unique<MathNodeSquareRoot>();
  node->init(this);
  return std::move(node);
}

void MathNodeSquareRoot::compute() {
  const auto &value_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toReal();

  result_pin.setData(qSqrt(value));
}
