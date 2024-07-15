/* ----------------------------------- Local -------------------------------- */
#include "command/change_string_node.h"

#include "event/string_node_change_event.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow_document.h>
/* -------------------------------------------------------------------------- */

/* ---------------------- SetStringNodeStringEmitterValue ------------------- */

SetStringNodeStringEmitterValue::SetStringNodeStringEmitterValue(
    flow_document::FlowDocument* document,
    QList<StringNodeStringEmitter*> nodes, QString value,
    egnite::Command* parent)
    : ChangeValue<StringNodeStringEmitter, QString>(
          QLatin1String("SetStringNodeStringEmitterValue"), document,
          std::move(nodes), value, parent) {
  const auto what = QObject::tr("Set Node(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Emiter Value");

  setText(QString("%1 %2").arg(what, action));
}

SetStringNodeStringEmitterValue::~SetStringNodeStringEmitterValue() = default;

QString SetStringNodeStringEmitterValue::getValue(
    const StringNodeStringEmitter* node) const {
  return node->getValue();
}

void SetStringNodeStringEmitterValue::setValue(StringNodeStringEmitter* node,
                                               const QString& value) {
  node->setValue(value);
  getDocument()->event(StringNodeStringEmittersChangeEvent(
      {node}, StringNodeStringEmittersChangeEvent::Property::Value));
}
