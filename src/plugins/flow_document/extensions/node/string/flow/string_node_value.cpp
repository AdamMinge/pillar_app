/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node_value.h"

#include "command/change_string_node.h"
#include "event/string_node_change_event.h"
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

/* ------------------------ StringNodeStringEmitterItem --------------------- */

StringNodeStringEmitterItem::StringNodeStringEmitterItem(
    flow_document::Node *node, flow_document::FlowDocument *document,
    QGraphicsItem *parent)
    : flow_document::NodeItem(node, document, parent),
      m_widget(new QLineEdit()),
      m_updating(false) {
  connect(m_widget.get(), &QLineEdit::textChanged, [this]() {
    if (!m_updating) apply();
  });

  connect(getDocument(), &flow_document::FlowDocument::event, this,
          &StringNodeStringEmitterItem::onEvent);
}

StringNodeStringEmitterItem::~StringNodeStringEmitterItem() = default;

QWidget *StringNodeStringEmitterItem::getEmbeddedWidget() const {
  return m_widget.get();
}

void StringNodeStringEmitterItem::onEvent(
    const flow_document::ChangeEvent &event) {
  flow_document::NodeItem::onEvent(event);

  if (event.getType() == StringNodeStringEmittersChangeEvent::type) {
    auto &e = static_cast<const StringNodeStringEmittersChangeEvent &>(event);
    if (e.getNodes().contains(getNode())) onUpdate(e);
  }
}

void StringNodeStringEmitterItem::onUpdate(
    const StringNodeStringEmittersChangeEvent &event) {
  QScopedValueRollback<bool> updating(m_updating, true);

  const auto node = static_cast<StringNodeStringEmitter *>(getNode());
  const auto properties = event.getProperties();

  using enum StringNodeStringEmittersChangeEvent::Property;
  if (properties & Value) {
    m_widget->setText(node->getValue());
  }
}

void StringNodeStringEmitterItem::apply() {
  getDocument()->getUndoStack()->push(new SetStringNodeStringEmitterValue(
      getDocument(), {static_cast<StringNodeStringEmitter *>(getNode())},
      m_widget->text()));
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

/* ----------------------- StringNodeStringReceiverItem --------------------- */

StringNodeStringReceiverItem::StringNodeStringReceiverItem(
    flow_document::Node *node, flow_document::FlowDocument *document,
    QGraphicsItem *parent)
    : flow_document::NodeItem(node, document, parent),
      m_widget(new QLineEdit()) {
  m_widget->setDisabled(true);
}

StringNodeStringReceiverItem::~StringNodeStringReceiverItem() = default;

QWidget *StringNodeStringReceiverItem::getEmbeddedWidget() const {
  return m_widget.get();
}