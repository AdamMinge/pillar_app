/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/component/scene/item/node_value_item.h"

#include "flow/logic_node/command/change_node_value.h"
#include "flow/logic_node/event/node_value_change_event.h"
#include "flow/logic_node/flow/value.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QScopedValueRollback>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/document.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------ LogicNodeBoolEmitterItem ------------------------ */

LogicNodeBoolEmitterItem::LogicNodeBoolEmitterItem(LogicNodeBoolEmitter *node,
                                                   FlowDocument *document,
                                                   QGraphicsItem *parent)
    : NodeItem(node, document, parent),
      m_widget(new QCheckBox(QObject::tr("Bool"))),
      m_updating(false) {
  connect(m_widget.get(), &QCheckBox::toggled, [this]() {
    if (!m_updating) apply();
  });

  connect(getDocument(), &FlowDocument::event, this,
          &LogicNodeBoolEmitterItem::onEvent);
}

LogicNodeBoolEmitterItem::~LogicNodeBoolEmitterItem() = default;

QWidget *LogicNodeBoolEmitterItem::getEmbeddedWidget() const {
  return m_widget.get();
}

void LogicNodeBoolEmitterItem::onEvent(const ChangeEvent &event) {
  NodeItem::onEvent(event);

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
    LogicNodeBoolReceiver *node, FlowDocument *document, QGraphicsItem *parent)
    : NodeItem(node, document, parent),
      m_widget(new QCheckBox(QObject::tr("Bool"))) {
  m_widget->setDisabled(true);
}

LogicNodeBoolReceiverItem::~LogicNodeBoolReceiverItem() = default;

QWidget *LogicNodeBoolReceiverItem::getEmbeddedWidget() const {
  return m_widget.get();
}

}  // namespace flow