#ifndef FLOW_DOCUMENT_NODE_PROPERTIES_H
#define FLOW_DOCUMENT_NODE_PROPERTIES_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/object_properties.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Node;

/* ------------------------------ NodeProperties ---------------------------- */

class FLOW_DOCUMENT_API NodeProperties : public ObjectProperties {
  Q_OBJECT

 public:
  enum Property { Name, Visible, Position };

 public:
  explicit NodeProperties(QObject* parent = nullptr);
  ~NodeProperties() override;

  [[nodiscard]] Node* getNode() const;

  void addProperty(const QString& name, const QVariant& value) override;
  void removeProperty(const QString& name) override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

 protected:
  void updateObject() override;

  void applyCustom(const QString& name, const QVariant& value) override;
  void applyObject(size_t id, const QVariant& value) override;

 private:
  void initNodeProperty();
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_PROPERTIES_H