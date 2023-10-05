/* ----------------------------------- Local -------------------------------- */
#include "string_node_value.h"
/* -------------------------------------------------------------------------- */

/* -------------------------- StringNodeStringEmitter ----------------------- */

StringNodeStringEmitter::StringNodeStringEmitter() : m_widget(new QLineEdit()) {
  setName(QObject::tr("STRING_EMITTER"));

  auto out_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(out_pin), 0);

  m_widget->connect(m_widget.get(), &QLineEdit::textChanged,
                    [this]() { compute(); });
}

StringNodeStringEmitter::~StringNodeStringEmitter() = default;

QWidget *StringNodeStringEmitter::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> StringNodeStringEmitter::clone() const {
  auto node = std::make_unique<StringNodeStringEmitter>();
  node->init(this);
  return std::move(node);
}

void StringNodeStringEmitter::compute() {
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);
  const auto value = m_widget->text();

  out_pin.setData(value);
}

/* ------------------------- StringNodeStringReceiver ----------------------- */

StringNodeStringReceiver::StringNodeStringReceiver()
    : m_widget(new QLineEdit()) {
  setName(QObject::tr("STRING_RECEIVER"));

  auto in_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(in_pin), 0);

  m_widget->setDisabled(true);
}

StringNodeStringReceiver::~StringNodeStringReceiver() = default;

QWidget *StringNodeStringReceiver::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> StringNodeStringReceiver::clone() const {
  auto node = std::make_unique<StringNodeStringReceiver>();
  node->init(this);
  return std::move(node);
}

void StringNodeStringReceiver::compute() {
  auto &in_pin = getPin(flow_document::Pin::Type::In, 0);
  const auto value = in_pin.getData().toString();

  m_widget->setText(value);
}
