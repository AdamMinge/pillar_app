#ifndef FLOW_LOGIC_NODE_CHANGE_LOGIC_NODE_H
#define FLOW_LOGIC_NODE_CHANGE_LOGIC_NODE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/command/change_value.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/export.h"
#include "flow/logic_node/flow/value.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ----------------------- SetLogicNodeBoolEmitterValue --------------------- */

class LIB_FLOW_LOGIC_NODE_API SetLogicNodeBoolEmitterValue
    : public ChangeValue<LogicNodeBoolEmitter, bool> {
 public:
  explicit SetLogicNodeBoolEmitterValue(FlowDocument* document,
                                        QList<LogicNodeBoolEmitter*> nodes,
                                        bool value,
                                        pillar::Command* parent = nullptr);
  ~SetLogicNodeBoolEmitterValue() override;

 protected:
  [[nodiscard]] bool getValue(const LogicNodeBoolEmitter* node) const override;
  void setValue(LogicNodeBoolEmitter* node, const bool& value) override;
};

}  // namespace flow

#endif  // FLOW_LOGIC_NODE_CHANGE_LOGIC_NODE_H