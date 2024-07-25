#ifndef CHANGE_STRING_NODE_H
#define CHANGE_STRING_NODE_H

/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/command/change_value.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/export.h"
#include "flow/string_node/flow/value.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ---------------------- SetStringNodeStringEmitterValue ------------------- */

class LIB_FLOW_STRING_NODE_API SetStringNodeStringEmitterValue
    : public ChangeValue<StringNodeStringEmitter, QString> {
 public:
  explicit SetStringNodeStringEmitterValue(
      FlowDocument* document, QList<StringNodeStringEmitter*> nodes,
      QString value, pillar::Command* parent = nullptr);
  ~SetStringNodeStringEmitterValue() override;

 protected:
  [[nodiscard]] QString getValue(
      const StringNodeStringEmitter* node) const override;
  void setValue(StringNodeStringEmitter* node, const QString& value) override;
};

}  // namespace flow

#endif  // CHANGE_STRING_NODE_H