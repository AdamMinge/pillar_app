/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node_division.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Dividend = 0, Divisor = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------ MathNodeDivision -------------------------- */

MathNodeDivision::MathNodeDivision() {
  setName(QObject::tr("DIVISION"));

  getPin(flow_document::Pin::Type::In, PinIn::Dividend).setCaption("Dividend");
  getPin(flow_document::Pin::Type::In, PinIn::Divisor).setCaption("Divisor");
}

MathNodeDivision::~MathNodeDivision() = default;

std::unique_ptr<flow_document::Node> MathNodeDivision::clone() const {
  auto node = std::make_unique<MathNodeDivision>();
  node->init(this);
  return std::move(node);
}

void MathNodeDivision::compute() {
  const auto &dividend_pin =
      getPin(flow_document::Pin::Type::In, PinIn::Dividend);
  const auto &divisor_pin =
      getPin(flow_document::Pin::Type::In, PinIn::Divisor);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto dividend = dividend_pin.getData().toReal();
  const auto divisor = divisor_pin.getData().toReal();

  result_pin.setData(dividend / divisor);
}