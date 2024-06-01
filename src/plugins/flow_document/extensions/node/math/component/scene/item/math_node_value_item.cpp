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

/* ------------------------ MathNodeFloatEmitterItem ------------------------ */

MathNodeFloatEmitterItem::MathNodeFloatEmitterItem(
    MathNodeFloatEmitter *node, flow_document::FlowDocument *document,
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

/* ----------------------- MathNodeFloatReceiverItem ------------------------ */

MathNodeFloatReceiverItem::MathNodeFloatReceiverItem(
    MathNodeFloatReceiver *node, flow_document::FlowDocument *document,
    QGraphicsItem *parent)
    : flow_document::NodeItem(node, document, parent),
      m_widget(new QDoubleSpinBox()) {
  m_widget->setDisabled(true);
}

MathNodeFloatReceiverItem::~MathNodeFloatReceiverItem() = default;

QWidget *MathNodeFloatReceiverItem::getEmbeddedWidget() const {
  return m_widget.get();
}
