/* ----------------------------------- Local -------------------------------- */
#include "component/scene/item/logic_node_value_item.h"

#include "command/change_logic_node.h"
#include "event/logic_node_change_event.h"
#include "flow/logic_node_value.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QScopedValueRollback>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow_document.h>
/* -------------------------------------------------------------------------- */

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
