/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/component/scene/item/node_value_item.h"

#include "flow/string_node/command/change_node_value.h"
#include "flow/string_node/event/node_value_change_event.h"
#include "flow/string_node/flow/value.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QScopedValueRollback>
/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/document.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------ StringNodeStringEmitterItem --------------------- */

StringNodeStringEmitterItem::StringNodeStringEmitterItem(
    StringNodeStringEmitter *node, FlowDocument *document,
    QGraphicsItem *parent)
    : NodeItem(node, document, parent),
      m_widget(new QLineEdit()),
      m_updating(false) {
  connect(m_widget.get(), &QLineEdit::textChanged, [this]() {
    if (!m_updating) apply();
  });

  connect(getDocument(), &FlowDocument::event, this,
          &StringNodeStringEmitterItem::onEvent);
}

StringNodeStringEmitterItem::~StringNodeStringEmitterItem() = default;

QWidget *StringNodeStringEmitterItem::getEmbeddedWidget() const {
  return m_widget.get();
}

void StringNodeStringEmitterItem::onEvent(const ChangeEvent &event) {
  NodeItem::onEvent(event);

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
    StringNodeStringReceiver *node, FlowDocument *document,
    QGraphicsItem *parent)
    : NodeItem(node, document, parent), m_widget(new QLineEdit()) {
  m_widget->setDisabled(true);
}

StringNodeStringReceiverItem::~StringNodeStringReceiverItem() = default;

QWidget *StringNodeStringReceiverItem::getEmbeddedWidget() const {
  return m_widget.get();
}

}  // namespace flow