#ifndef STRING_NODE_CHANGE_EVENT_H
#define STRING_NODE_CHANGE_EVENT_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/event/change_event.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "flow/string_node_value.h"
/* -------------------------------------------------------------------------- */

/* --------------------- StringNodeStringEmittersChangeEvent ---------------- */

class STRING_NODE_API StringNodeStringEmittersChangeEvent
    : public flow_document::ChangeEvent {
 public:
  static constexpr QLatin1String type =
      QLatin1String("StringNodeStringEmittersChangeEvent");

  enum class Property {
    Value = 1 << 0,
  };
  Q_DECLARE_FLAGS(Properties, Property)

 public:
  explicit StringNodeStringEmittersChangeEvent(
      QList<StringNodeStringEmitter*> nodes, Properties properties);
  ~StringNodeStringEmittersChangeEvent() override;

  [[nodiscard]] const QList<StringNodeStringEmitter*>& getNodes() const;
  [[nodiscard]] Properties getProperties() const;

  [[nodiscard]] bool contains(StringNodeStringEmitter* node) const;

 private:
  QList<StringNodeStringEmitter*> m_nodes;
  Properties m_properties;
};

#endif  // STRING_NODE_CHANGE_EVENT_H
