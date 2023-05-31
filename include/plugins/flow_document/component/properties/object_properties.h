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
class QtVariantEditorFactory;
class QtTreePropertyBrowser;
class QtVariantProperty;

}  // namespace utils

namespace flow_document {

class Object;
class ChangeEvent;

class FlowDocument;
class Node;
class Layer;

/* ----------------------------- ObjectProperties --------------------------- */

class FLOW_DOCUMENT_API ObjectProperties : public QObject {
  Q_OBJECT

 public:
  explicit ObjectProperties(QObject* parent = nullptr);
  ~ObjectProperties() override;

  [[nodiscard]] virtual QList<utils::QtProperty*> getProperties() const = 0;

  void setDocument(FlowDocument* document);
  [[nodiscard]] FlowDocument* getDocument() const;

  void setObject(Object* object);
  [[nodiscard]] Object* getObject() const;

  virtual void setFactoryForManager(utils::QtTreePropertyBrowser* browser);
  virtual void unsetFactoryForManager(utils::QtTreePropertyBrowser* browser);

 protected:
  virtual void onEvent(const ChangeEvent& event);

  virtual void update();
  virtual void updateObject();
  virtual void updateCustom();

  virtual void applyValue(utils::QtProperty* property, QVariant value);

  utils::QtProperty* createGroup(const QString& name,
                                 utils::QtProperty* parent = nullptr);
  utils::QtVariantProperty* createProperty(int id, int type,
                                           const QString& name,
                                           utils::QtProperty* parent = nullptr);

  [[nodiscard]] utils::QtVariantProperty* getPropertyById(int id) const;
  [[nodiscard]] int getIdByProperty(utils::QtProperty* property) const;

  [[nodiscard]] utils::QtProperty* getCustomProperty() const;

 private:
  utils::QtProperty* createCustomProperty(utils::QtProperty* parent = nullptr);

 private:
  FlowDocument* m_document;
  Object* m_object;

  bool m_updating;

  utils::QtGroupPropertyManager* m_group_property_manager;
  utils::QtVariantPropertyManager* m_variant_property_manager;

  utils::QtVariantEditorFactory* m_variant_editor_factory;

  QHash<int, utils::QtVariantProperty*> m_id_to_property;
  QHash<utils::QtProperty*, int> m_property_to_id;

  utils::QtProperty* m_customProperty;
};

/* ------------------------------ LayerProperties --------------------------- */

class FLOW_DOCUMENT_API LayerProperties : public ObjectProperties {
  Q_OBJECT

 public:
  enum Property { Name, Visible, Locked, Opacity, Position };

 public:
  explicit LayerProperties(QObject* parent = nullptr);
  ~LayerProperties() override;

  [[nodiscard]] QList<utils::QtProperty*> getProperties() const override;
  [[nodiscard]] Layer* getLayer() const;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

 protected:
  void updateObject() override;
  void applyValue(utils::QtProperty* property, QVariant value) override;

  [[nodiscard]] utils::QtProperty* createLayerProperty();

 private:
  utils::QtProperty* m_layerProperty;
};

/* ------------------------------ NodeProperties ---------------------------- */

class FLOW_DOCUMENT_API NodeProperties : public ObjectProperties {
  Q_OBJECT

 public:
  enum Property { Name, Visible, Position };

 public:
  explicit NodeProperties(QObject* parent = nullptr);
  ~NodeProperties() override;

  [[nodiscard]] QList<utils::QtProperty*> getProperties() const override;
  [[nodiscard]] Node* getNode() const;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

 protected:
  void updateObject() override;
  void applyValue(utils::QtProperty* property, QVariant value) override;

  [[nodiscard]] utils::QtProperty* createNodeProperty();

 private:
  utils::QtProperty* m_nodeProperty;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECT_PROPERTIES_H