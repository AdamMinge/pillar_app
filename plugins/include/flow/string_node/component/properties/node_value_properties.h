#ifndef STRING_NODE_VALUE_PROPERTIES_H
#define STRING_NODE_VALUE_PROPERTIES_H

/* ------------------------------------- Qt --------------------------------- */
#include <QCheckBox>
#include <QScopedPointer>
/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/component/properties/node_properties.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* --------------------- StringNodeStringEmitterProperties ------------------ */

class LIB_FLOW_STRING_NODE_API StringNodeStringEmitterProperties
    : public NodeProperties {
  Q_OBJECT

 public:
  enum Property { Value = PropertiesCount };

 public:
  explicit StringNodeStringEmitterProperties(QObject* parent = nullptr);
  ~StringNodeStringEmitterProperties() override;

  void init() override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

  void updateObject() override;
  void applyObject(size_t id, const QVariant& value) override;
};

}  // namespace flow

#endif  // STRING_NODE_VALUE_PROPERTIES_H