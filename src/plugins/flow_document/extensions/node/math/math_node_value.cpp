/* ----------------------------------- Local -------------------------------- */
#include "math_node_value.h"
/* -------------------------------------------------------------------------- */

/* -------------------------- MathNodeFloatEmitter -------------------------- */

MathNodeFloatEmitter::MathNodeFloatEmitter() : m_widget(new QDoubleSpinBox()) {
  setName(QObject::tr("FLOAT_EMITTER"));

  auto out_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(out_pin), 0);

  m_widget->connect(m_widget.get(), &QDoubleSpinBox::valueChanged,
                    [this]() { compute(); });
}

MathNodeFloatEmitter::~MathNodeFloatEmitter() = default;

QWidget *MathNodeFloatEmitter::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> MathNodeFloatEmitter::clone() const {
  auto node = std::make_unique<MathNodeFloatEmitter>();
  node->init(this);
  return std::move(node);
}

void MathNodeFloatEmitter::compute() {
  auto &out_pin = getPin(flow_document::Pin::Type::Out, 0);
  const auto value = m_widget->value();

  out_pin.setData(value);
}

/* -------------------------- MathNodeFloatReceiver ------------------------- */

MathNodeFloatReceiver::MathNodeFloatReceiver()
    : m_widget(new QDoubleSpinBox()) {
  setName(QObject::tr("FLOAT_RECEIVER"));

  auto in_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(in_pin), 0);

  m_widget->setDisabled(true);
}

MathNodeFloatReceiver::~MathNodeFloatReceiver() = default;

QWidget *MathNodeFloatReceiver::getEmbeddedWidget() const {
  return m_widget.get();
}

std::unique_ptr<flow_document::Node> MathNodeFloatReceiver::clone() const {
  auto node = std::make_unique<MathNodeFloatReceiver>();
  node->init(this);
  return std::move(node);
}

void MathNodeFloatReceiver::compute() {
  auto &in_pin = getPin(flow_document::Pin::Type::In, 0);
  const auto value = in_pin.getData().toReal();

  m_widget->setValue(value);
}
