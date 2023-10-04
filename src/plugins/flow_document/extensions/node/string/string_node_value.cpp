/* ----------------------------------- Local -------------------------------- */
#include "string_node_value.h"
/* -------------------------------------------------------------------------- */

/* -------------------------- StringNodeValueEmitter ------------------------ */

StringNodeValueEmitter::StringNodeValueEmitter() : m_widget(new QLineEdit()) {
  setName(QObject::tr("STRING_EMITTER"));

  auto out_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(out_pin), 0);

  m_widget->connect(m_widget.get(), &QLineEdit::textChanged,
                    [this]() { compute(); });
}

StringNodeValueEmitter::~StringNodeValueEmitter() = default;

QWidget *StringNodeValueEmitter::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> StringNodeValueEmitter::clone() const {
  auto node = std::make_unique<StringNodeValueEmitter>();
  node->init(this);
  return std::move(node);
}

void StringNodeValueEmitter::compute() {
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);
  const auto value = m_widget->text();

  out_pin.setData(value);
}

/* ------------------------- StringNodeValueReceiver ------------------------ */

StringNodeValueReceiver::StringNodeValueReceiver() : m_widget(new QLineEdit()) {
  setName(QObject::tr("STRING_RECEIVER"));

  auto in_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(in_pin), 0);

  m_widget->setDisabled(true);
}

StringNodeValueReceiver::~StringNodeValueReceiver() = default;

QWidget *StringNodeValueReceiver::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> StringNodeValueReceiver::clone() const {
  auto node = std::make_unique<StringNodeValueReceiver>();
  node->init(this);
  return std::move(node);
}

void StringNodeValueReceiver::compute() {
  auto &in_pin = getPin(flow_document::Pin::Type::In, 0);
  const auto value = in_pin.getData().toString();

  m_widget->setText(value);
}
