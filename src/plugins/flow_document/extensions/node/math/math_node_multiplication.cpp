/* ----------------------------------- Local -------------------------------- */
#include "math_node_multiplication.h"
/* -------------------------------------------------------------------------- */

/* --------------------------- MathNodeMultiplication ----------------------- */

MathNodeMultiplication::MathNodeMultiplication() {
  setName(QObject::tr("Multiplication"));
}

MathNodeMultiplication::~MathNodeMultiplication() = default;

std::unique_ptr<flow_document::Node> MathNodeMultiplication::clone() const {
  auto node = std::make_unique<MathNodeMultiplication>();
  node->init(this);
  return std::move(node);
}

void MathNodeMultiplication::compute() {
  const auto &in_pin_0 = getPin(flow_document::Pin::Type::In, 0);
  const auto &in_pin_1 = getPin(flow_document::Pin::Type::In, 1);
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);

  const auto value_A = in_pin_0.getData().toReal();
  const auto value_B = in_pin_1.getData().toReal();

  out_pin.setData(value_A * value_B);
}