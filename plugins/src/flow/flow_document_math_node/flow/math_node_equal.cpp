/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node_equal.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Lhs = 0, Rhs = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------- MathNodeEqual ---------------------------- */

MathNodeEqual::MathNodeEqual() { setName(QObject::tr("EQUAL")); }

MathNodeEqual::~MathNodeEqual() = default;

std::unique_ptr<flow_document::Node> MathNodeEqual::clone() const {
  auto node = std::make_unique<MathNodeEqual>();
  node->init(this);
  return std::move(node);
}

void MathNodeEqual::compute() {
  auto &lhs_pin = getPin(flow_document::Pin::Type::In, PinIn::Lhs);
  auto &rhs_pin = getPin(flow_document::Pin::Type::In, PinIn::Rhs);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto lhs = lhs_pin.getData().toReal();
  const auto rhs = rhs_pin.getData().toReal();

  result_pin.setData(lhs == rhs);
}
