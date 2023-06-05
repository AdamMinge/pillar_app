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

/* -------------------------------- Properties ------------------------------ */

class FLOW_DOCUMENT_API Properties : public QObject {
  Q_OBJECT

 public:
  explicit Properties(const QString& name, QObject* parent = nullptr);
  ~Properties() override;

  [[nodiscard]] utils::QtProperty* getRoot() const;

  [[nodiscard]] qsizetype size() const;
  [[nodiscard]] bool contains(utils::QtProperty* property) const;

  void setFactoryForManager(utils::QtTreePropertyBrowser* browser);
  void unsetFactoryForManager(utils::QtTreePropertyBrowser* browser);

  utils::QtVariantProperty* createProperty(size_t id, int type,
                                           const QString& name,
                                           utils::QtProperty* parent = nullptr);

  [[nodiscard]] utils::QtVariantProperty* getPropertyById(size_t id) const;
  [[nodiscard]] std::optional<size_t> getIdByProperty(
      utils::QtProperty* property) const;

  void clear();

 Q_SIGNALS:
  void valueChanged(size_t id, QVariant value);

 private:
  utils::QtProperty* createGroup(const QString& name,
                                 utils::QtProperty* parent = nullptr);

 private:
  utils::QtGroupPropertyManager* m_group_manager;
  utils::QtVariantPropertyManager* m_property_manager;

  utils::QtVariantEditorFactory* m_editor_factory;

  QHash<size_t, utils::QtVariantProperty*> m_id_to_property;
  QHash<utils::QtProperty*, size_t> m_property_to_id;

  utils::QtProperty* m_root;
};

/* ----------------------------- ObjectProperties --------------------------- */

class FLOW_DOCUMENT_API ObjectProperties : public QObject {
  Q_OBJECT

 public:
  explicit ObjectProperties(const QString& name, QObject* parent = nullptr);
  ~ObjectProperties() override;

  [[nodiscard]] QList<utils::QtProperty*> getProperties() const;

  void setDocument(FlowDocument* document);
  [[nodiscard]] FlowDocument* getDocument() const;

  void setObject(Object* object);
  [[nodiscard]] Object* getObject() const;

  [[nodiscard]] bool isCustomProperty(utils::QtProperty* property) const;

  virtual void addProperty(const QString& name, const QVariant& value) = 0;
  virtual void removeProperty(const QString& name) = 0;

  void setFactoryForManager(utils::QtTreePropertyBrowser* browser);
  void unsetFactoryForManager(utils::QtTreePropertyBrowser* browser);

 protected Q_SLOTS:
  virtual void onEvent(const ChangeEvent& event);

  void applyCustom(size_t id, const QVariant& value);
  virtual void applyCustom(const QString& name, const QVariant& value);
  virtual void applyObject(size_t id, const QVariant& value);

 protected:
  [[nodiscard]] Properties* getCustomProperties() const;
  [[nodiscard]] Properties* getObjectProperties() const;

  void update();
  void updateCustom();
  virtual void updateObject();

 private:
  FlowDocument* m_document;
  Object* m_object;

  bool m_updating;
  Properties* m_custom_properties;
  Properties* m_object_properties;
};

/* ------------------------------ LayerProperties --------------------------- */

class FLOW_DOCUMENT_API LayerProperties : public ObjectProperties {
  Q_OBJECT

 public:
  enum Property { Name, Visible, Locked, Opacity, Position };

 public:
  explicit LayerProperties(QObject* parent = nullptr);
  ~LayerProperties() override;

  [[nodiscard]] Layer* getLayer() const;

  void addProperty(const QString& name, const QVariant& value) override;
  void removeProperty(const QString& name) override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent& event) override;

 protected:
  void updateObject() override;

  void applyCustom(const QString& name, const QVariant& value) override;
  void applyObject(size_t id, const QVariant& value) override;

 private:
  void initLayerProperty();
};

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

#endif  // FLOW_DOCUMENT_OBJECT_PROPERTIES_H