#ifndef MATH_NODE_VALUE_PROPERTIES_H
#define MATH_NODE_VALUE_PROPERTIES_H

/* ------------------------------------- Qt --------------------------------- */
#include <QCheckBox>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/component/properties/node_properties.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/math_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ---------------------- MathNodeDoubleEmitterProperties ------------------- */

class LIB_FLOW_MATH_NODE_API MathNodeDoubleEmitterProperties
    : public NodeProperties {
  Q_OBJECT

 public:
  enum Property { Value = PropertiesCount };

 public:
  explicit MathNodeDoubleEmitterProperties(QObject* parent = nullptr);
  ~MathNodeDoubleEmitterProperties() override;

  void init() override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

  void updateObject() override;
  void applyObject(size_t id, const QVariant& value) override;
};

}  // namespace flow

#endif  // MATH_NODE_VALUE_PROPERTIES_H