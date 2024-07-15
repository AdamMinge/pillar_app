#ifndef CHANGE_STRING_NODE_H
#define CHANGE_STRING_NODE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/command/change_value.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "flow/string_node_value.h"
/* -------------------------------------------------------------------------- */

/* ---------------------- SetStringNodeStringEmitterValue ------------------- */

class STRING_NODE_API SetStringNodeStringEmitterValue
    : public flow_document::ChangeValue<StringNodeStringEmitter, QString> {
 public:
  explicit SetStringNodeStringEmitterValue(
      flow_document::FlowDocument* document,
      QList<StringNodeStringEmitter*> nodes, QString value,
      egnite::Command* parent = nullptr);
  ~SetStringNodeStringEmitterValue() override;

 protected:
  [[nodiscard]] QString getValue(
      const StringNodeStringEmitter* node) const override;
  void setValue(StringNodeStringEmitter* node, const QString& value) override;
};

#endif  // CHANGE_STRING_NODE_H