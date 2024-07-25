#ifndef FLOW_LOGIC_NODE_NODE_VALUE_CHANGE_EVENT_H
#define FLOW_LOGIC_NODE_NODE_VALUE_CHANGE_EVENT_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/event/change_event.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/export.h"
#include "flow/logic_node/flow/value.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ---------------------- LogicNodeBoolEmittersChangeEvent ------------------ */

class LIB_FLOW_LOGIC_NODE_API LogicNodeBoolEmittersChangeEvent
    : public ChangeEvent {
 public:
  static constexpr QLatin1String type =
      QLatin1String("LogicNodeBoolEmittersChangeEvent");

  enum class Property {
    Value = 1 << 0,
  };
  Q_DECLARE_FLAGS(Properties, Property)

 public:
  explicit LogicNodeBoolEmittersChangeEvent(QList<LogicNodeBoolEmitter*> nodes,
                                            Properties properties);
  ~LogicNodeBoolEmittersChangeEvent() override;

  [[nodiscard]] const QList<LogicNodeBoolEmitter*>& getNodes() const;
  [[nodiscard]] Properties getProperties() const;

  [[nodiscard]] bool contains(LogicNodeBoolEmitter* node) const;

 private:
  QList<LogicNodeBoolEmitter*> m_nodes;
  Properties m_properties;
};

}  // namespace flow

#endif  // FLOW_LOGIC_NODE_NODE_VALUE_CHANGE_EVENT_H
