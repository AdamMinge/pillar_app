#ifndef FLOW_DOCUMENT_LAYER_PROPERTIES_H
#define FLOW_DOCUMENT_LAYER_PROPERTIES_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/object_properties.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Layer;

/* ------------------------------ LayerProperties --------------------------- */

class FLOW_DOCUMENT_API LayerProperties : public ObjectProperties {
  Q_OBJECT

 public:
  enum Property { Name, Visible, Locked, Opacity, Position, PropertiesCount };

 public:
  explicit LayerProperties(QObject* parent = nullptr);
  ~LayerProperties() override;

  void init() override;

  [[nodiscard]] Layer* getLayer() const;

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

#endif  // FLOW_DOCUMENT_LAYER_PROPERTIES_H