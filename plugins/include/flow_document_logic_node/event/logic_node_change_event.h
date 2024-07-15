#ifndef LOGIC_NODE_CHANGE_EVENT_H
#define LOGIC_NODE_CHANGE_EVENT_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/event/change_event.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "flow/logic_node_value.h"
/* -------------------------------------------------------------------------- */

/* ---------------------- LogicNodeBoolEmittersChangeEvent ------------------ */

class LOGIC_NODE_API LogicNodeBoolEmittersChangeEvent
    : public flow_document::ChangeEvent {
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

#endif  // LOGIC_NODE_CHANGE_EVENT_H
