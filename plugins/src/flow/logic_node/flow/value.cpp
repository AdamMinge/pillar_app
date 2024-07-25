/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/flow/value.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Qtils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

namespace flow {

/* -------------------------- LogicNodeBoolEmitter -------------------------- */

LogicNodeBoolEmitter::LogicNodeBoolEmitter() : m_value(false) {
  setName(QObject::tr("BOOL_EMITTER"));

  auto value_pin = Pin({}, "Q");
  insertPin(Pin::Type::Out, std::move(value_pin), PinOut::Result);
}

LogicNodeBoolEmitter::~LogicNodeBoolEmitter() = default;

std::unique_ptr<Node> LogicNodeBoolEmitter::clone() const {
  auto node = std::make_unique<LogicNodeBoolEmitter>();
  node->init(this);
  return std::move(node);
}

void LogicNodeBoolEmitter::setValue(bool value) { m_value = value; }

bool LogicNodeBoolEmitter::getValue() const { return m_value; }

void LogicNodeBoolEmitter::compute() {
  auto &value_pin = getPin(Pin::Type::Out, PinOut::Result);
  const auto value = getValue();

  value_pin.setData(value);
}

/* -------------------------- LogicNodeBoolReceiver ------------------------- */

LogicNodeBoolReceiver::LogicNodeBoolReceiver() : m_value(false) {
  setName(QObject::tr("BOOL_RECEIVER"));

  auto result_pin = Pin({}, "A");
  insertPin(Pin::Type::In, std::move(result_pin), PinIn::Value);
}

LogicNodeBoolReceiver::~LogicNodeBoolReceiver() = default;

void LogicNodeBoolReceiver::setValue(bool value) { m_value = value; }

bool LogicNodeBoolReceiver::getValue() const { return m_value; }

std::unique_ptr<Node> LogicNodeBoolReceiver::clone() const {
  auto node = std::make_unique<LogicNodeBoolReceiver>();
  node->init(this);
  return std::move(node);
}

void LogicNodeBoolReceiver::compute() {
  auto &result_pin = getPin(Pin::Type::In, PinIn::Value);
  m_value = result_pin.getData().toBool();
}

}  // namespace flow