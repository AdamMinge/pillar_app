/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node_value.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

/* -------------------------- StringNodeStringEmitter ----------------------- */

StringNodeStringEmitter::StringNodeStringEmitter() : m_value("") {
  setName(QObject::tr("STRING_EMITTER"));

  auto out_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(out_pin), PinOut::Result);
}

StringNodeStringEmitter::~StringNodeStringEmitter() = default;

std::unique_ptr<flow_document::Node> StringNodeStringEmitter::clone() const {
  auto node = std::make_unique<StringNodeStringEmitter>();
  node->init(this);
  return std::move(node);
}

void StringNodeStringEmitter::setValue(QString value) { m_value = value; }

QString StringNodeStringEmitter::getValue() const { return m_value; }

void StringNodeStringEmitter::compute() {
  auto &out_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);
  const auto value = getValue();

  out_pin.setData(value);
}

/* ------------------------- StringNodeStringReceiver ----------------------- */

StringNodeStringReceiver::StringNodeStringReceiver() : m_value("") {
  setName(QObject::tr("STRING_RECEIVER"));

  auto in_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(in_pin), PinIn::Value);
}

StringNodeStringReceiver::~StringNodeStringReceiver() = default;

std::unique_ptr<flow_document::Node> StringNodeStringReceiver::clone() const {
  auto node = std::make_unique<StringNodeStringReceiver>();
  node->init(this);
  return std::move(node);
}

void StringNodeStringReceiver::setValue(QString value) { m_value = value; }

QString StringNodeStringReceiver::getValue() const { return m_value; }

void StringNodeStringReceiver::compute() {
  auto &in_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  m_value = in_pin.getData().toString();
}
