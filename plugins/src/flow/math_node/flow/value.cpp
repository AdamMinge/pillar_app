/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/flow/value.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* -------------------------- MathNodeDoubleEmitter ------------------------- */

MathNodeDoubleEmitter::MathNodeDoubleEmitter() : m_value(0) {
  setName(QObject::tr("DOUBLE_EMITTER"));

  auto value_pin = Pin({}, "Q");
  insertPin(Pin::Type::Out, std::move(value_pin), PinOut::Result);
}

MathNodeDoubleEmitter::~MathNodeDoubleEmitter() = default;

std::unique_ptr<Node> MathNodeDoubleEmitter::clone() const {
  auto node = std::make_unique<MathNodeDoubleEmitter>();
  node->init(this);
  return std::move(node);
}

void MathNodeDoubleEmitter::setValue(double value) { m_value = value; }

double MathNodeDoubleEmitter::getValue() const { return m_value; }

void MathNodeDoubleEmitter::compute() {
  auto &value_pin = getPin(Pin::Type::Out, PinOut::Result);
  const auto value = getValue();

  value_pin.setData(value);
}

/* -------------------------- MathNodeDoubleReceiver ------------------------ */

MathNodeDoubleReceiver::MathNodeDoubleReceiver() : m_value(0) {
  setName(QObject::tr("DOUBLE_RECEIVER"));

  auto result_pin = Pin({}, "A");
  insertPin(Pin::Type::In, std::move(result_pin), PinIn::Value);
}

MathNodeDoubleReceiver::~MathNodeDoubleReceiver() = default;

std::unique_ptr<Node> MathNodeDoubleReceiver::clone() const {
  auto node = std::make_unique<MathNodeDoubleReceiver>();
  node->init(this);
  return std::move(node);
}

void MathNodeDoubleReceiver::setValue(double value) { m_value = value; }

double MathNodeDoubleReceiver::getValue() const { return m_value; }

void MathNodeDoubleReceiver::compute() {
  auto &result_pin = getPin(Pin::Type::In, PinIn::Value);
  m_value = result_pin.getData().toReal();
}

}  // namespace flow