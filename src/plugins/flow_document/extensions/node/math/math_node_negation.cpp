/* ----------------------------------- Local -------------------------------- */
#include "math_node_negation.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------ MathNodeNegation -------------------------- */

MathNodeNegation::MathNodeNegation() { setName(QObject::tr("NEGATION")); }

MathNodeNegation::~MathNodeNegation() = default;

std::unique_ptr<flow_document::Node> MathNodeNegation::clone() const {
  auto node = std::make_unique<MathNodeNegation>();
  node->init(this);
  return std::move(node);
}

void MathNodeNegation::compute() {
  const auto &value_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto value = value_pin.getData().toReal();

  result_pin.setData(-value);
}