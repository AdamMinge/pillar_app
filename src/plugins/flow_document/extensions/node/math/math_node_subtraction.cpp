/* ----------------------------------- Local -------------------------------- */
#include "math_node_subtraction.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Minuend = 0, Subtrahend = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ----------------------------- MathNodeSubtraction ------------------------ */

MathNodeSubtraction::MathNodeSubtraction() {
  setName(QObject::tr("SUBTRACTION"));

  getPin(flow_document::Pin::Type::In, Minuend).setCaption("Minuend");
  getPin(flow_document::Pin::Type::In, Subtrahend).setCaption("Subtrahend");
}

MathNodeSubtraction::~MathNodeSubtraction() = default;

std::unique_ptr<flow_document::Node> MathNodeSubtraction::clone() const {
  auto node = std::make_unique<MathNodeSubtraction>();
  node->init(this);
  return std::move(node);
}

void MathNodeSubtraction::compute() {
  const auto &minuend_pin = getPin(flow_document::Pin::Type::In, Minuend);
  const auto &subtrahend_pin = getPin(flow_document::Pin::Type::In, Subtrahend);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, Result);

  const auto minuend = minuend_pin.getData().toReal();
  const auto subtrahend = subtrahend_pin.getData().toReal();

  result_pin.setData(minuend - subtrahend);
}