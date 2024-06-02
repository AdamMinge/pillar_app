/* ----------------------------------- Local -------------------------------- */
#include "component/scene/item/math_node_value_item.h"

#include "command/change_math_node.h"
#include "event/math_node_change_event.h"
#include "flow/math_node_value.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QScopedValueRollback>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow_document.h>
/* -------------------------------------------------------------------------- */

/* ------------------------ MathNodeDoubleEmitterItem ----------------------- */

MathNodeDoubleEmitterItem::MathNodeDoubleEmitterItem(
    MathNodeDoubleEmitter *node, flow_document::FlowDocument *document,
    QGraphicsItem *parent)
    : flow_document::NodeItem(node, document, parent),
      m_widget(new QDoubleSpinBox()),
      m_updating(false) {
  m_widget->setRange(std::numeric_limits<double>::lowest(),
                     std::numeric_limits<double>::max());

  connect(m_widget.get(), &QDoubleSpinBox::valueChanged, [this]() {
    if (!m_updating) apply();
  });

  connect(getDocument(), &flow_document::FlowDocument::event, this,
          &MathNodeDoubleEmitterItem::onEvent);
}

MathNodeDoubleEmitterItem::~MathNodeDoubleEmitterItem() = default;

QWidget *MathNodeDoubleEmitterItem::getEmbeddedWidget() const {
  return m_widget.get();
}

void MathNodeDoubleEmitterItem::onEvent(
    const flow_document::ChangeEvent &event) {
  flow_document::NodeItem::onEvent(event);

  if (event.getType() == MathNodeDoubleEmittersChangeEvent::type) {
    auto &e = static_cast<const MathNodeDoubleEmittersChangeEvent &>(event);
    if (e.getNodes().contains(getNode())) onUpdate(e);
  }
}

void MathNodeDoubleEmitterItem::onUpdate(
    const MathNodeDoubleEmittersChangeEvent &event) {
  QScopedValueRollback<bool> updating(m_updating, true);

  const auto node = static_cast<MathNodeDoubleEmitter *>(getNode());
  const auto properties = event.getProperties();

  using enum MathNodeDoubleEmittersChangeEvent::Property;
  if (properties & Value) {
    m_widget->setValue(node->getValue());
  }
}

void MathNodeDoubleEmitterItem::apply() {
  getDocument()->getUndoStack()->push(new SetMathNodeDoubleEmitterValue(
      getDocument(), {static_cast<MathNodeDoubleEmitter *>(getNode())},
      m_widget->value()));
}

/* ----------------------- MathNodeDoubleReceiverItem ----------------------- */

MathNodeDoubleReceiverItem::MathNodeDoubleReceiverItem(
    MathNodeDoubleReceiver *node, flow_document::FlowDocument *document,
    QGraphicsItem *parent)
    : flow_document::NodeItem(node, document, parent),
      m_widget(new QDoubleSpinBox()) {
  m_widget->setDisabled(true);
}

MathNodeDoubleReceiverItem::~MathNodeDoubleReceiverItem() = default;

QWidget *MathNodeDoubleReceiverItem::getEmbeddedWidget() const {
  return m_widget.get();
}
