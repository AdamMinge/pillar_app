#ifndef FLOW_DOCUMENT_NODE_PROPERTIES_H
#define FLOW_DOCUMENT_NODE_PROPERTIES_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/properties/object_properties.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class Node;

/* ------------------------------ NodeProperties ---------------------------- */

class LIB_FLOW_DOCUMENT_API NodeProperties : public ObjectProperties {
  Q_OBJECT

 public:
  enum Property { Name, Visible, Position, PropertiesCount };

 public:
  explicit NodeProperties(QObject* parent = nullptr);
  ~NodeProperties() override;

  void init() override;

  [[nodiscard]] Node* getNode() const;

  void addProperty(const QString& name, const QVariant& value) override;
  void removeProperty(const QString& name) override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

 protected:
  void updateObject() override;

  void applyCustom(const QString& name, const QVariant& value) override;
  void applyObject(size_t id, const QVariant& value) override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_NODE_PROPERTIES_H