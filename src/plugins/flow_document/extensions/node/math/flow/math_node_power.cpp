/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node_power.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Base = 0, Exponent = 1 };
enum PinOut { Result = 0 };

}  // namespace

/* -------------------------------- MathNodePower --------------------------- */

MathNodePower::MathNodePower() {
  setName(QObject::tr("POWER"));

  getPin(flow_document::Pin::Type::In, PinIn::Base).setCaption("Base");
  getPin(flow_document::Pin::Type::In, PinIn::Exponent).setCaption("Exponent");
}

MathNodePower::~MathNodePower() = default;

std::unique_ptr<flow_document::Node> MathNodePower::clone() const {
  auto node = std::make_unique<MathNodePower>();
  node->init(this);
  return std::move(node);
}

void MathNodePower::compute() {
  const auto &base_pin = getPin(flow_document::Pin::Type::In, PinIn::Base);
  const auto &exponent_pin =
      getPin(flow_document::Pin::Type::In, PinIn::Exponent);
  auto &result_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);

  const auto base = base_pin.getData().toReal();
  const auto exponent = exponent_pin.getData().toReal();

  result_pin.setData(qPow(base, exponent));
}
