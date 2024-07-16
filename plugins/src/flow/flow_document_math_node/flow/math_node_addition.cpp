/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node_addition.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Augend = 0, Addend = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* ------------------------------ MathNodeAddition -------------------------- */

MathNodeAddition::MathNodeAddition() {
  setName(QObject::tr("ADDITION"));

  getPin(flow_document::Pin::Type::In, PinIn::Augend).setCaption("Augend");
  getPin(flow_document::Pin::Type::In, PinIn::Addend).setCaption("Addend");
}

MathNodeAddition::~MathNodeAddition() = default;

std::unique_ptr<flow_document::Node> MathNodeAddition::clone() const {
  auto node = std::make_unique<MathNodeAddition>();
  node->init(this);
  return std::move(node);
}

void MathNodeAddition::compute() {
  const auto &augend_pin = getPin(flow_document::Pin::Type::In, PinIn::Augend);
  const auto &addend_pin = getPin(flow_document::Pin::Type::In, PinIn::Addend);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto augend = augend_pin.getData().toReal();
  const auto addend = addend_pin.getData().toReal();

  result_pin.setData(augend + addend);
}
