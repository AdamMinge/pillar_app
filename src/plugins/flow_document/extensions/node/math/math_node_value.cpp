/* ----------------------------------- Local -------------------------------- */
#include "math_node_value.h"
/* -------------------------------------------------------------------------- */

/* -------------------------- MathNodeValueEmitter -------------------------- */

MathNodeValueEmitter::MathNodeValueEmitter() : m_widget(new QSpinBox()) {
  setName(QObject::tr("MATH_EMITTER"));

  auto out_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(out_pin), 0);

  m_widget->connect(m_widget.get(), &QSpinBox::valueChanged,
                    [this]() { compute(); });
}

MathNodeValueEmitter::~MathNodeValueEmitter() = default;

QWidget *MathNodeValueEmitter::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> MathNodeValueEmitter::clone() const {
  auto node = std::make_unique<MathNodeValueEmitter>();
  node->init(this);
  return std::move(node);
}

void MathNodeValueEmitter::compute() {
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);
  const auto value = m_widget->value();

  out_pin.setData(value);
}

/* -------------------------- MathNodeValueReceiver ------------------------- */

MathNodeValueReceiver::MathNodeValueReceiver() : m_widget(new QSpinBox()) {
  setName(QObject::tr("MATH_RECEIVER"));

  auto in_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(in_pin), 0);

  m_widget->setDisabled(true);
}

MathNodeValueReceiver::~MathNodeValueReceiver() = default;

QWidget *MathNodeValueReceiver::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> MathNodeValueReceiver::clone() const {
  auto node = std::make_unique<MathNodeValueReceiver>();
  node->init(this);
  return std::move(node);
}

void MathNodeValueReceiver::compute() {
  auto &in_pin = getPin(flow_document::Pin::Type::In, 0);
  const auto value = in_pin.getData().toReal();

  m_widget->setValue(value);
}
