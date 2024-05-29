/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node_value.h"

#include "command/change_math_node.h"
#include "event/math_node_change_event.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QScopedValueRollback>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow_document.h>
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

/* ------------------------ MathNodeFloatEmitterItem ------------------------ */

MathNodeFloatEmitterItem::MathNodeFloatEmitterItem(
    flow_document::Node *node, flow_document::FlowDocument *document,
    QGraphicsItem *parent)
    : flow_document::NodeItem(node, document, parent),
      m_widget(new QDoubleSpinBox()),
      m_updating(false) {
  connect(m_widget.get(), &QDoubleSpinBox::valueChanged, [this]() {
    if (!m_updating) apply();
  });

  connect(getDocument(), &flow_document::FlowDocument::event, this,
          &MathNodeFloatEmitterItem::onEvent);
}

MathNodeFloatEmitterItem::~MathNodeFloatEmitterItem() = default;

QWidget *MathNodeFloatEmitterItem::getEmbeddedWidget() const {
  return m_widget.get();
}

void MathNodeFloatEmitterItem::onEvent(
    const flow_document::ChangeEvent &event) {
  flow_document::NodeItem::onEvent(event);

  if (event.getType() == MathNodeFloatEmittersChangeEvent::type) {
    auto &e = static_cast<const MathNodeFloatEmittersChangeEvent &>(event);
    if (e.getNodes().contains(getNode())) onUpdate(e);
  }
}

void MathNodeFloatEmitterItem::onUpdate(
    const MathNodeFloatEmittersChangeEvent &event) {
  QScopedValueRollback<bool> updating(m_updating, true);

  const auto node = static_cast<MathNodeFloatEmitter *>(getNode());
  const auto properties = event.getProperties();

  using enum MathNodeFloatEmittersChangeEvent::Property;
  if (properties & Value) {
    m_widget->setValue(node->getValue());
  }
}

void MathNodeFloatEmitterItem::apply() {
  getDocument()->getUndoStack()->push(new SetMathNodeFloatEmitterValue(
      getDocument(), {static_cast<MathNodeFloatEmitter *>(getNode())},
      m_widget->value()));
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

/* ----------------------- MathNodeFloatReceiverItem ------------------------ */

MathNodeFloatReceiverItem::MathNodeFloatReceiverItem(
    flow_document::Node *node, flow_document::FlowDocument *document,
    QGraphicsItem *parent)
    : flow_document::NodeItem(node, document, parent),
      m_widget(new QDoubleSpinBox()) {
  m_widget->setDisabled(true);
}

MathNodeFloatReceiverItem::~MathNodeFloatReceiverItem() = default;

QWidget *MathNodeFloatReceiverItem::getEmbeddedWidget() const {
  return m_widget.get();
}
