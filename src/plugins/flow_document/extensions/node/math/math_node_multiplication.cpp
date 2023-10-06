/* ----------------------------------- Local -------------------------------- */
#include "math_node_multiplication.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Multiplier = 0, Multiplicand = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* --------------------------- MathNodeMultiplication ----------------------- */

MathNodeMultiplication::MathNodeMultiplication() {
  setName(QObject::tr("MULTIPLICATION"));

  getPin(flow_document::Pin::Type::In, Multiplier).setCaption("Multiplier");
  getPin(flow_document::Pin::Type::In, Multiplicand).setCaption("Multiplicand");
}

MathNodeMultiplication::~MathNodeMultiplication() = default;

std::unique_ptr<flow_document::Node> MathNodeMultiplication::clone() const {
  auto node = std::make_unique<MathNodeMultiplication>();
  node->init(this);
  return std::move(node);
}

void MathNodeMultiplication::compute() {
  const auto &multiplier_pin = getPin(flow_document::Pin::Type::In, Multiplier);
  const auto &multiplicand_pin =
      getPin(flow_document::Pin::Type::In, Multiplicand);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, Result);

  const auto multiplier = multiplier_pin.getData().toReal();
  const auto multiplicand = multiplicand_pin.getData().toReal();

  result_pin.setData(multiplier * multiplicand);
}