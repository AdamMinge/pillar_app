/* ----------------------------------- Local -------------------------------- */
#include "component/scene/item/string_node_value_item.h"

#include "command/change_string_node.h"
#include "event/string_node_change_event.h"
#include "flow/string_node_value.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QScopedValueRollback>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow_document.h>
/* -------------------------------------------------------------------------- */

/* ------------------------ StringNodeStringEmitterItem --------------------- */

StringNodeStringEmitterItem::StringNodeStringEmitterItem(
    StringNodeStringEmitter *node, flow_document::FlowDocument *document,
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

/* ----------------------- StringNodeStringReceiverItem --------------------- */

StringNodeStringReceiverItem::StringNodeStringReceiverItem(
    StringNodeStringReceiver *node, flow_document::FlowDocument *document,
    QGraphicsItem *parent)
    : flow_document::NodeItem(node, document, parent),
      m_widget(new QLineEdit()) {
  m_widget->setDisabled(true);
}

StringNodeStringReceiverItem::~StringNodeStringReceiverItem() = default;

QWidget *StringNodeStringReceiverItem::getEmbeddedWidget() const {
  return m_widget.get();
}