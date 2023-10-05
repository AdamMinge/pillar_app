/* ----------------------------------- Local -------------------------------- */
#include "math_node_square_root.h"
/* -------------------------------------------------------------------------- */

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
  const auto &in_pin = getPin(flow_document::Pin::Type::In, 0);
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);

  const auto value = in_pin.getData().toReal();

  out_pin.setData(qSqrt(value));
}
