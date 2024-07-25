#ifndef FLOW_LOGIC_NODE_NODE_VALUE_PROPERTIES_H
#define FLOW_LOGIC_NODE_NODE_VALUE_PROPERTIES_H

/* ------------------------------------- Qt --------------------------------- */
#include <QCheckBox>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/component/properties/node_properties.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ---------------------- LogicNodeBoolEmitterProperties -------------------- */

class LIB_FLOW_LOGIC_NODE_API LogicNodeBoolEmitterProperties
    : public NodeProperties {
  Q_OBJECT

 public:
  enum Property { Value = PropertiesCount };

 public:
  explicit LogicNodeBoolEmitterProperties(QObject* parent = nullptr);
  ~LogicNodeBoolEmitterProperties() override;

  void init() override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

  void updateObject() override;
  void applyObject(size_t id, const QVariant& value) override;
};

}  // namespace flow

#endif  // FLOW_LOGIC_NODE_NODE_VALUE_PROPERTIES_H