/* ----------------------------------- Local -------------------------------- */
#include "math_node_negation.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------ MathNodeNegation -------------------------- */

MathNodeNegation::MathNodeNegation() { setName(QObject::tr("NEGATION")); }

MathNodeNegation::~MathNodeNegation() = default;

std::unique_ptr<flow_document::Node> MathNodeNegation::clone() const {
  auto node = std::make_unique<MathNodeNegation>();
  node->init(this);
  return std::move(node);
}

void MathNodeNegation::compute() {
  const auto &in_pin = getPin(flow_document::Pin::Type::In, 0);
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);

  const auto value = in_pin.getData().toReal();

  out_pin.setData(-value);
}