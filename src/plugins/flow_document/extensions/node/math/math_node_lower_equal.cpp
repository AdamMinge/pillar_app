/* ----------------------------------- Local -------------------------------- */
#include "math_node_lower_equal.h"
/* -------------------------------------------------------------------------- */

MathNodeLowerEqual::MathNodeLowerEqual() {
  setName(QObject::tr("LOWER EQUAL"));
}

MathNodeLowerEqual::~MathNodeLowerEqual() = default;

std::unique_ptr<flow_document::Node> MathNodeLowerEqual::clone() const {
  auto node = std::make_unique<MathNodeLowerEqual>();
  node->init(this);
  return std::move(node);
}

void MathNodeLowerEqual::compute() {
  auto &in_pin_0 = getPin(flow_document::Pin::Type::In, 0);
  auto &in_pin_1 = getPin(flow_document::Pin::Type::In, 1);
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);

  const auto value_A = in_pin_0.getData().toReal();
  const auto value_B = in_pin_1.getData().toReal();

  out_pin.setData(value_A <= value_B);
}