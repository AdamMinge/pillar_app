/* ----------------------------------- Local -------------------------------- */
#include "math_node_not_equal.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Lhs = 0, Rhs = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------ MathNodeNotEqual -------------------------- */

MathNodeNotEqual::MathNodeNotEqual() { setName(QObject::tr("NOT EQUAL")); }

MathNodeNotEqual::~MathNodeNotEqual() = default;

std::unique_ptr<flow_document::Node> MathNodeNotEqual::clone() const {
  auto node = std::make_unique<MathNodeNotEqual>();
  node->init(this);
  return std::move(node);
}

void MathNodeNotEqual::compute() {
  auto &lhs_pin = getPin(flow_document::Pin::Type::In, Lhs);
  auto &rhs_pin = getPin(flow_document::Pin::Type::In, Rhs);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, Result);

  const auto lhs = lhs_pin.getData().toReal();
  const auto rhs = rhs_pin.getData().toReal();

  result_pin.setData(lhs != rhs);
}