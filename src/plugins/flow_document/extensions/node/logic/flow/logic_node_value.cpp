/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node_value.h"

#include "command/change_logic_node.h"
#include "event/logic_node_change_event.h"
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

/* -------------------------- LogicNodeBoolEmitter -------------------------- */

LogicNodeBoolEmitter::LogicNodeBoolEmitter() : m_value(false) {
  setName(QObject::tr("BOOL_EMITTER"));

  auto value_pin = flow_document::Pin({}, "Q");
  insertPin(flow_document::Pin::Type::Out, std::move(value_pin),
            PinOut::Result);
}

LogicNodeBoolEmitter::~LogicNodeBoolEmitter() = default;

std::unique_ptr<flow_document::Node> LogicNodeBoolEmitter::clone() const {
  auto node = std::make_unique<LogicNodeBoolEmitter>();
  node->init(this);
  return std::move(node);
}

void LogicNodeBoolEmitter::setValue(bool value) { m_value = value; }

bool LogicNodeBoolEmitter::getValue() const { return m_value; }

void LogicNodeBoolEmitter::compute() {
  auto &value_pin = getPin(flow_document::Pin::Type::Out, PinOut::Result);
  const auto value = getValue();

  value_pin.setData(value);
}

/* ------------------------ LogicNodeBoolEmitterItem ------------------------ */

LogicNodeBoolEmitterItem::LogicNodeBoolEmitterItem(
    LogicNodeBoolEmitter *node, flow_document::FlowDocument *document,
    QGraphicsItem *parent)
    : flow_document::NodeItem(node, document, parent),
      m_widget(new QCheckBox(QObject::tr("Bool"))),
      m_updating(false) {
  connect(m_widget.get(), &QCheckBox::toggled, [this]() {
    if (!m_updating) apply();
  });

  connect(getDocument(), &flow_document::FlowDocument::event, this,
          &LogicNodeBoolEmitterItem::onEvent);
}

LogicNodeBoolEmitterItem::~LogicNodeBoolEmitterItem() = default;

QWidget *LogicNodeBoolEmitterItem::getEmbeddedWidget() const {
  return m_widget.get();
}

void LogicNodeBoolEmitterItem::onEvent(
    const flow_document::ChangeEvent &event) {
  flow_document::NodeItem::onEvent(event);

  if (event.getType() == LogicNodeBoolEmittersChangeEvent::type) {
    auto &e = static_cast<const LogicNodeBoolEmittersChangeEvent &>(event);
    if (e.getNodes().contains(getNode())) onUpdate(e);
  }
}

void LogicNodeBoolEmitterItem::onUpdate(
    const LogicNodeBoolEmittersChangeEvent &event) {
  QScopedValueRollback<bool> updating(m_updating, true);

  const auto node = static_cast<LogicNodeBoolEmitter *>(getNode());
  const auto properties = event.getProperties();

  using enum LogicNodeBoolEmittersChangeEvent::Property;
  if (properties & Value) {
    m_widget->setChecked(node->getValue());
  }
}

void LogicNodeBoolEmitterItem::apply() {
  getDocument()->getUndoStack()->push(new SetLogicNodeBoolEmitterValue(
      getDocument(), {static_cast<LogicNodeBoolEmitter *>(getNode())},
      m_widget->checkState() == Qt::Checked));
}

/* -------------------------- LogicNodeBoolReceiver ------------------------- */

LogicNodeBoolReceiver::LogicNodeBoolReceiver() : m_value(false) {
  setName(QObject::tr("BOOL_RECEIVER"));

  auto result_pin = flow_document::Pin({}, "A");
  insertPin(flow_document::Pin::Type::In, std::move(result_pin), PinIn::Value);
}

LogicNodeBoolReceiver::~LogicNodeBoolReceiver() = default;

void LogicNodeBoolReceiver::setValue(bool value) { m_value = value; }

bool LogicNodeBoolReceiver::getValue() const { return m_value; }

std::unique_ptr<flow_document::Node> LogicNodeBoolReceiver::clone() const {
  auto node = std::make_unique<LogicNodeBoolReceiver>();
  node->init(this);
  return std::move(node);
}

void LogicNodeBoolReceiver::compute() {
  auto &result_pin = getPin(flow_document::Pin::Type::In, PinIn::Value);
  m_value = result_pin.getData().toBool();
}

/* ----------------------- LogicNodeBoolReceiverItem ------------------------ */

LogicNodeBoolReceiverItem::LogicNodeBoolReceiverItem(
    LogicNodeBoolReceiver *node, flow_document::FlowDocument *document,
    QGraphicsItem *parent)
    : flow_document::NodeItem(node, document, parent),
      m_widget(new QCheckBox(QObject::tr("Bool"))) {
  m_widget->setDisabled(true);
}

LogicNodeBoolReceiverItem::~LogicNodeBoolReceiverItem() = default;

QWidget *LogicNodeBoolReceiverItem::getEmbeddedWidget() const {
  return m_widget.get();
}
