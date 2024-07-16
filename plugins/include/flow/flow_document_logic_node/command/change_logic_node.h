#ifndef CHANGE_LOGIC_NODE_H
#define CHANGE_LOGIC_NODE_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/command/change_value.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "flow/logic_node_value.h"
/* -------------------------------------------------------------------------- */

/* ----------------------- SetLogicNodeBoolEmitterValue --------------------- */

class LOGIC_NODE_API SetLogicNodeBoolEmitterValue
    : public flow_document::ChangeValue<LogicNodeBoolEmitter, bool> {
 public:
  explicit SetLogicNodeBoolEmitterValue(flow_document::FlowDocument* document,
                                        QList<LogicNodeBoolEmitter*> nodes,
                                        bool value,
                                        pillar::Command* parent = nullptr);
  ~SetLogicNodeBoolEmitterValue() override;

 protected:
  [[nodiscard]] bool getValue(const LogicNodeBoolEmitter* node) const override;
  void setValue(LogicNodeBoolEmitter* node, const bool& value) override;
};

#endif  // CHANGE_LOGIC_NODE_H