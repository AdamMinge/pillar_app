#ifndef FLOW_DOCUMENT_OBJECT_PROPERTIES_H
#define FLOW_DOCUMENT_OBJECT_PROPERTIES_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QHash>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

class QtProperty;
class QtGroupPropertyManager;
class QtVariantPropertyManager;

}  // namespace utils

namespace flow_document {

class Object;
class ChangeEvent;

/* ----------------------------- ObjectProperties --------------------------- */

class FLOW_DOCUMENT_API ObjectProperties : public QObject {
  Q_OBJECT

 public:
  using TypeId = int;

 public:
  explicit ObjectProperties(QObject* parent = nullptr);
  ~ObjectProperties() override;

  [[nodiscard]] virtual QString supportedClass() const = 0;

  void setObject(Object* object);
  [[nodiscard]] Object* getObject() const;

  [[nodiscard]] utils::QtProperty* getRootProperty();

  virtual void onEvent(const ChangeEvent& event);

 protected:
  [[nodiscard]] virtual utils::QtProperty* createObjectProperty();
  [[nodiscard]] virtual utils::QtProperty* createCustomProperty();

  [[nodiscard]] virtual utils::QtProperty* createGroup(const QString& name);
  [[nodiscard]] virtual utils::QtProperty* createProperty(int id, TypeId type,
                                                          const QString& name);
  [[nodiscard]] virtual utils::QtProperty* addProperty(
      int id, TypeId type, const QString& name, utils::QtProperty* parent);

 private:
  Object* m_object;

  utils::QtGroupPropertyManager* m_group_property_manager;
  utils::QtVariantPropertyManager* m_variant_property_manager;
  utils::QtProperty* m_root_property;

  QHash<int, utils::QtProperty*> m_id_to_property;
  QHash<utils::QtProperty*, int> m_property_to_id;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::ObjectProperties,
                    "org.flow.ObjectProperties")

namespace flow_document {

/* ------------------------------ LayerProperties --------------------------- */

class FLOW_DOCUMENT_API LayerProperties : public ObjectProperties {
  Q_OBJECT
  Q_INTERFACES(flow_document::ObjectProperties);

 public:
  explicit LayerProperties(QObject* parent = nullptr);
  ~LayerProperties() override;

  [[nodiscard]] QString supportedClass() const override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

 protected:
  [[nodiscard]] utils::QtProperty* createObjectProperty() override;
};

/* ------------------------------ NodeProperties ---------------------------- */

class FLOW_DOCUMENT_API NodeProperties : public ObjectProperties {
  Q_OBJECT
  Q_INTERFACES(flow_document::ObjectProperties);

 public:
  explicit NodeProperties(QObject* parent = nullptr);
  ~NodeProperties() override;

  [[nodiscard]] QString supportedClass() const override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

 protected:
  [[nodiscard]] utils::QtProperty* createObjectProperty() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECT_PROPERTIES_H