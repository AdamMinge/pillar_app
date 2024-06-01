#ifndef LOGIC_NODE_VALUE_PROPERTIES_H
#define LOGIC_NODE_VALUE_PROPERTIES_H

/* ------------------------------------- Qt --------------------------------- */
#include <QCheckBox>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/properties/node_properties.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/object_properties.h"
/* -------------------------------------------------------------------------- */

/* ---------------------- LogicNodeBoolEmitterProperties -------------------- */

class LOGIC_NODE_API LogicNodeBoolEmitterProperties
    : public flow_document::NodeProperties {
  Q_OBJECT

 public:
  enum Property { Value = PropertiesCount };

 public:
  explicit LogicNodeBoolEmitterProperties(QObject* parent = nullptr);
  ~LogicNodeBoolEmitterProperties() override;

  void init() override;

 protected Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent& event) override;

  void updateObject() override;
  void applyObject(size_t id, const QVariant& value) override;
};

#endif  // LOGIC_NODE_VALUE_PROPERTIES_H