#ifndef FLOW_DOCUMENT_CONNECTION_PROPERTIES_H
#define FLOW_DOCUMENT_CONNECTION_PROPERTIES_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/object_properties.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Connection;

/* --------------------------- ConnectionProperties ------------------------- */

class FLOW_DOCUMENT_API ConnectionProperties : public ObjectProperties {
  Q_OBJECT

 public:
  enum Property { Name, Visible, PropertiesCount };

 public:
  explicit ConnectionProperties(QObject* parent = nullptr);
  ~ConnectionProperties() override;

  void init() override;

  [[nodiscard]] Connection* getConnection() const;

  void addProperty(const QString& name, const QVariant& value) override;
  void removeProperty(const QString& name) override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

 protected:
  void updateObject() override;

  void applyCustom(const QString& name, const QVariant& value) override;
  void applyObject(size_t id, const QVariant& value) override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONNECTION_PROPERTIES_H