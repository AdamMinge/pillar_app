/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/command/change_node_value.h"

#include "flow/string_node/event/node_value_change_event.h"
/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/document.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ---------------------- SetStringNodeStringEmitterValue ------------------- */

SetStringNodeStringEmitterValue::SetStringNodeStringEmitterValue(
    FlowDocument* document, QList<StringNodeStringEmitter*> nodes,
    QString value, pillar::Command* parent)
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

}  // namespace flow