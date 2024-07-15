#ifndef MATH_NODE_VALUE_PROPERTIES_H
#define MATH_NODE_VALUE_PROPERTIES_H

/* ------------------------------------- Qt --------------------------------- */
#include <QCheckBox>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/properties/node_properties.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

/* ---------------------- MathNodeDoubleEmitterProperties ------------------- */

class MATH_NODE_API MathNodeDoubleEmitterProperties
    : public flow_document::NodeProperties {
  Q_OBJECT

 public:
  enum Property { Value = PropertiesCount };

 public:
  explicit MathNodeDoubleEmitterProperties(QObject* parent = nullptr);
  ~MathNodeDoubleEmitterProperties() override;

  void init() override;

 protected Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent& event) override;

  void updateObject() override;
  void applyObject(size_t id, const QVariant& value) override;
};

#endif  // MATH_NODE_VALUE_PROPERTIES_H