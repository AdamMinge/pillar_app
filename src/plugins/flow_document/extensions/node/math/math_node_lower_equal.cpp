/* ----------------------------------- Local -------------------------------- */
#include "math_node_lower_equal.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Lhs = 0, Rhs = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ---------------------------- MathNodeLowerEqual -------------------------- */

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
  auto &lhs_pin = getPin(flow_document::Pin::Type::In, PinIn::Lhs);
  auto &rhs_pin = getPin(flow_document::Pin::Type::In, PinIn::Rhs);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto lhs = lhs_pin.getData().toReal();
  const auto rhs = rhs_pin.getData().toReal();

  result_pin.setData(lhs <= rhs);
}