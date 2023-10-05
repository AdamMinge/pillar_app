/* ----------------------------------- Local -------------------------------- */
#include "math_node_not_equal.h"
/* -------------------------------------------------------------------------- */

MathNodeNotEqual::MathNodeNotEqual() { setName(QObject::tr("NOT EQUAL")); }

MathNodeNotEqual::~MathNodeNotEqual() = default;

std::unique_ptr<flow_document::Node> MathNodeNotEqual::clone() const {
  auto node = std::make_unique<MathNodeNotEqual>();
  node->init(this);
  return std::move(node);
}

void MathNodeNotEqual::compute() {
  auto &in_pin_0 = getPin(flow_document::Pin::Type::In, 0);
  auto &in_pin_1 = getPin(flow_document::Pin::Type::In, 1);
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);

  const auto value_A = in_pin_0.getData().toReal();
  const auto value_B = in_pin_1.getData().toReal();

  out_pin.setData(value_A != value_B);
}