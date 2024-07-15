#ifndef STRING_NODE_VALUE_PROPERTIES_H
#define STRING_NODE_VALUE_PROPERTIES_H

/* ------------------------------------- Qt --------------------------------- */
#include <QCheckBox>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/properties/node_properties.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

/* --------------------- StringNodeStringEmitterProperties ------------------ */

class STRING_NODE_API StringNodeStringEmitterProperties
    : public flow_document::NodeProperties {
  Q_OBJECT

 public:
  enum Property { Value = PropertiesCount };

 public:
  explicit StringNodeStringEmitterProperties(QObject* parent = nullptr);
  ~StringNodeStringEmitterProperties() override;

  void init() override;

 protected Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent& event) override;

  void updateObject() override;
  void applyObject(size_t id, const QVariant& value) override;
};

#endif  // STRING_NODE_VALUE_PROPERTIES_H