/* ----------------------------------- Local -------------------------------- */
#include "math_node_power.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- MathNodePower --------------------------- */

MathNodePower::MathNodePower() { setName(QObject::tr("POWER")); }

MathNodePower::~MathNodePower() = default;

std::unique_ptr<flow_document::Node> MathNodePower::clone() const {
  auto node = std::make_unique<MathNodePower>();
  node->init(this);
  return std::move(node);
}

void MathNodePower::compute() {
  const auto &in_pin_0 = getPin(flow_document::Pin::Type::In, 0);
  const auto &in_pin_1 = getPin(flow_document::Pin::Type::In, 1);
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);

  const auto value_A = in_pin_0.getData().toReal();
  const auto value_B = in_pin_1.getData().toReal();

  out_pin.setData(qPow(value_A, value_B));
}
