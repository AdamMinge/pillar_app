/* ----------------------------------- Local -------------------------------- */
#include "math_node_value.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Utils -------------------------------- */

namespace {

enum PinIn { Value = 0 };
enum PinOut { Result = 0 };

}  // namespace

/* -------------------------- MathNodeFloatEmitter -------------------------- */

MathNodeFloatEmitter::MathNodeFloatEmitter() : m_widget(new QDoubleSpinBox()) {
  setName(QObject::tr("FLOAT_EMITTER"));

  auto value_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(value_pin),
            PinOut::Result);

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
  auto &value_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);
  const auto value = m_widget->value();

  value_pin.setData(value);
}

/* -------------------------- MathNodeFloatReceiver ------------------------- */

MathNodeFloatReceiver::MathNodeFloatReceiver()
    : m_widget(new QDoubleSpinBox()) {
  setName(QObject::tr("FLOAT_RECEIVER"));

  auto result_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(result_pin), PinIn::Value);

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
  auto &result_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  const auto value = result_pin.getData().toReal();

  m_widget->setValue(value);
}
