#ifndef MATH_NODE_CHANGE_EVENT_H
#define MATH_NODE_CHANGE_EVENT_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/event/change_event.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "flow/math_node_value.h"
/* -------------------------------------------------------------------------- */

/* ---------------------- MathNodeDoubleEmittersChangeEvent ----------------- */

class MATH_NODE_API MathNodeDoubleEmittersChangeEvent
    : public flow_document::ChangeEvent {
 public:
  static constexpr QLatin1String type =
      QLatin1String("MathNodeDoubleEmittersChangeEvent");

  enum class Property {
    Value = 1 << 0,
  };
  Q_DECLARE_FLAGS(Properties, Property)

 public:
  explicit MathNodeDoubleEmittersChangeEvent(
      QList<MathNodeDoubleEmitter*> nodes, Properties properties);
  ~MathNodeDoubleEmittersChangeEvent() override;

  [[nodiscard]] const QList<MathNodeDoubleEmitter*>& getNodes() const;
  [[nodiscard]] Properties getProperties() const;

  [[nodiscard]] bool contains(MathNodeDoubleEmitter* node) const;

 private:
  QList<MathNodeDoubleEmitter*> m_nodes;
  Properties m_properties;
};

#endif  // MATH_NODE_CHANGE_EVENT_H
