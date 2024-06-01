/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node_value.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

/* -------------------------- MathNodeFloatEmitter -------------------------- */

MathNodeFloatEmitter::MathNodeFloatEmitter() : m_value(0) {
  setName(QObject::tr("FLOAT_EMITTER"));

  auto value_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(value_pin),
            PinOut::Result);
}

MathNodeFloatEmitter::~MathNodeFloatEmitter() = default;

std::unique_ptr<flow_document::Node> MathNodeFloatEmitter::clone() const {
  auto node = std::make_unique<MathNodeFloatEmitter>();
  node->init(this);
  return std::move(node);
}

void MathNodeFloatEmitter::setValue(double value) { m_value = value; }

double MathNodeFloatEmitter::getValue() const { return m_value; }

void MathNodeFloatEmitter::compute() {
  auto &value_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);
  const auto value = getValue();

  value_pin.setData(value);
}

/* -------------------------- MathNodeFloatReceiver ------------------------- */

MathNodeFloatReceiver::MathNodeFloatReceiver() : m_value(0) {
  setName(QObject::tr("FLOAT_RECEIVER"));

  auto result_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(result_pin), PinIn::Value);
}

MathNodeFloatReceiver::~MathNodeFloatReceiver() = default;

std::unique_ptr<flow_document::Node> MathNodeFloatReceiver::clone() const {
  auto node = std::make_unique<MathNodeFloatReceiver>();
  node->init(this);
  return std::move(node);
}

void MathNodeFloatReceiver::setValue(double value) { m_value = value; }

double MathNodeFloatReceiver::getValue() const { return m_value; }

void MathNodeFloatReceiver::compute() {
  auto &result_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  m_value = result_pin.getData().toReal();
}
