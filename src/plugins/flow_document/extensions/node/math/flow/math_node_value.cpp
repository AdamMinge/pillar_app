/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node_value.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

/* -------------------------- MathNodeDoubleEmitter ------------------------- */

MathNodeDoubleEmitter::MathNodeDoubleEmitter() : m_value(0) {
  setName(QObject::tr("DOUBLE_EMITTER"));

  auto value_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(value_pin),
            PinOut::Result);
}

MathNodeDoubleEmitter::~MathNodeDoubleEmitter() = default;

std::unique_ptr<flow_document::Node> MathNodeDoubleEmitter::clone() const {
  auto node = std::make_unique<MathNodeDoubleEmitter>();
  node->init(this);
  return std::move(node);
}

void MathNodeDoubleEmitter::setValue(double value) { m_value = value; }

double MathNodeDoubleEmitter::getValue() const { return m_value; }

void MathNodeDoubleEmitter::compute() {
  auto &value_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);
  const auto value = getValue();

  value_pin.setData(value);
}

/* -------------------------- MathNodeDoubleReceiver ------------------------ */

MathNodeDoubleReceiver::MathNodeDoubleReceiver() : m_value(0) {
  setName(QObject::tr("DOUBLE_RECEIVER"));

  auto result_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(result_pin), PinIn::Value);
}

MathNodeDoubleReceiver::~MathNodeDoubleReceiver() = default;

std::unique_ptr<flow_document::Node> MathNodeDoubleReceiver::clone() const {
  auto node = std::make_unique<MathNodeDoubleReceiver>();
  node->init(this);
  return std::move(node);
}

void MathNodeDoubleReceiver::setValue(double value) { m_value = value; }

double MathNodeDoubleReceiver::getValue() const { return m_value; }

void MathNodeDoubleReceiver::compute() {
  auto &result_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  m_value = result_pin.getData().toReal();
}
