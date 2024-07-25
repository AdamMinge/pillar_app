/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/flow/value.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* -------------------------- StringNodeStringEmitter ----------------------- */

StringNodeStringEmitter::StringNodeStringEmitter() : m_value("") {
  setName(QObject::tr("STRING_EMITTER"));

  auto out_pin = Pin({}, "Q");
  insertPin(Pin::Type::Out, std::move(out_pin), PinOut::Result);
}

StringNodeStringEmitter::~StringNodeStringEmitter() = default;

std::unique_ptr<Node> StringNodeStringEmitter::clone() const {
  auto node = std::make_unique<StringNodeStringEmitter>();
  node->init(this);
  return std::move(node);
}

void StringNodeStringEmitter::setValue(QString value) { m_value = value; }

QString StringNodeStringEmitter::getValue() const { return m_value; }

void StringNodeStringEmitter::compute() {
  auto &out_pin = getPin(Pin::Type::Out, PinOut::Result);
  const auto value = getValue();

  out_pin.setData(value);
}

/* ------------------------- StringNodeStringReceiver ----------------------- */

StringNodeStringReceiver::StringNodeStringReceiver() : m_value("") {
  setName(QObject::tr("STRING_RECEIVER"));

  auto in_pin = Pin({}, "A");
  insertPin(Pin::Type::In, std::move(in_pin), PinIn::Value);
}

StringNodeStringReceiver::~StringNodeStringReceiver() = default;

std::unique_ptr<Node> StringNodeStringReceiver::clone() const {
  auto node = std::make_unique<StringNodeStringReceiver>();
  node->init(this);
  return std::move(node);
}

void StringNodeStringReceiver::setValue(QString value) { m_value = value; }

QString StringNodeStringReceiver::getValue() const { return m_value; }

void StringNodeStringReceiver::compute() {
  auto &in_pin = getPin(Pin::Type::In, PinIn::Value);
  m_value = in_pin.getData().toString();
}

}  // namespace flow
