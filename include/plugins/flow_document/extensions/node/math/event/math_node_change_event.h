#ifndef MATH_NODE_CHANGE_EVENT_H
#define MATH_NODE_CHANGE_EVENT_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/event/change_event.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "flow/math_node_value.h"
/* -------------------------------------------------------------------------- */

/* ---------------------- MathNodeFloatEmittersChangeEvent ------------------ */

class MATH_NODE_API MathNodeFloatEmittersChangeEvent
    : public flow_document::ChangeEvent {
 public:
  static constexpr QLatin1String type =
      QLatin1String("MathNodeFloatEmittersChangeEvent");

  enum class Property {
    Value = 1 << 0,
  };
  Q_DECLARE_FLAGS(Properties, Property)

 public:
  explicit MathNodeFloatEmittersChangeEvent(QList<MathNodeFloatEmitter*> nodes,
                                            Properties properties);
  ~MathNodeFloatEmittersChangeEvent() override;

  [[nodiscard]] const QList<MathNodeFloatEmitter*>& getNodes() const;
  [[nodiscard]] Properties getProperties() const;

  [[nodiscard]] bool contains(MathNodeFloatEmitter* node) const;

 private:
  QList<MathNodeFloatEmitter*> m_nodes;
  Properties m_properties;
};

#endif  // MATH_NODE_CHANGE_EVENT_H
