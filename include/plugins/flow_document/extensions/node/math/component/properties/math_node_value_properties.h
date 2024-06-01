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

/* ---------------------- MathNodeFloatEmitterProperties -------------------- */

class MATH_NODE_API MathNodeFloatEmitterProperties
    : public flow_document::NodeProperties {
  Q_OBJECT

 public:
  enum Property { Value = PropertiesCount };

 public:
  explicit MathNodeFloatEmitterProperties(QObject* parent = nullptr);
  ~MathNodeFloatEmitterProperties() override;

  void init() override;

 protected Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent& event) override;

  void updateObject() override;
  void applyObject(size_t id, const QVariant& value) override;
};

#endif  // MATH_NODE_VALUE_PROPERTIES_H