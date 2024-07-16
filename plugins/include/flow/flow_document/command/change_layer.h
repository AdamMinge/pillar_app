#ifndef FLOW_DOCUMENT_CHANGE_LAYER_H
#define FLOW_DOCUMENT_CHANGE_LAYER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QVariantMap>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/change_value.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class Layer;

/* ------------------------------ SetLayersVisible -------------------------- */

class FLOW_DOCUMENT_API SetLayersVisible : public ChangeValue<Layer, bool> {
 public:
  explicit SetLayersVisible(FlowDocument* document, QList<Layer*> layers,
                            bool visible, Command* parent = nullptr);
  ~SetLayersVisible() override;

 protected:
  [[nodiscard]] bool getValue(const Layer* layer) const override;
  void setValue(Layer* layer, const bool& visible) override;
};

/* ------------------------------ SetLayersLocked --------------------------- */

class FLOW_DOCUMENT_API SetLayersLocked : public ChangeValue<Layer, bool> {
 public:
  explicit SetLayersLocked(FlowDocument* document, QList<Layer*> layers,
                           bool locked, Command* parent = nullptr);
  ~SetLayersLocked() override;

 protected:
  [[nodiscard]] bool getValue(const Layer* layer) const override;
  void setValue(Layer* layer, const bool& locked) override;
};

/* ------------------------------- SetLayersName ---------------------------- */

class FLOW_DOCUMENT_API SetLayersName : public ChangeValue<Layer, QString> {
 public:
  explicit SetLayersName(FlowDocument* document, QList<Layer*> layers,
                         QString name, Command* parent = nullptr);
  ~SetLayersName() override;

 protected:
  [[nodiscard]] QString getValue(const Layer* layer) const override;
  void setValue(Layer* layer, const QString& name) override;
};

/* ------------------------------ SetLayersOpacity -------------------------- */

class FLOW_DOCUMENT_API SetLayersOpacity : public ChangeValue<Layer, qreal> {
 public:
  explicit SetLayersOpacity(FlowDocument* document, QList<Layer*> layers,
                            qreal opacity, Command* parent = nullptr);
  ~SetLayersOpacity() override;

 protected:
  [[nodiscard]] qreal getValue(const Layer* layer) const override;
  void setValue(Layer* layer, const qreal& opacity) override;
};

/* ----------------------------- SetLayersPosition -------------------------- */

class FLOW_DOCUMENT_API SetLayersPosition : public ChangeValue<Layer, QPointF> {
 public:
  explicit SetLayersPosition(FlowDocument* document, QList<Layer*> layers,
                             QPointF position, Command* parent = nullptr);
  ~SetLayersPosition() override;

 protected:
  [[nodiscard]] QPointF getValue(const Layer* layer) const override;
  void setValue(Layer* layer, const QPointF& position) override;
};

/* -------------------------- SetLayersCustomProperty ----------------------- */

class FLOW_DOCUMENT_API SetLayersCustomProperty
    : public ChangeValue<Layer, QVariant> {
 public:
  explicit SetLayersCustomProperty(FlowDocument* document, QList<Layer*> layers,
                                   QString property, QVariant value,
                                   Command* parent = nullptr);
  ~SetLayersCustomProperty() override;

 protected:
  [[nodiscard]] QVariant getValue(const Layer* layer) const override;
  void setValue(Layer* layer, const QVariant& value) override;

 private:
  QString m_property;
};

/* ------------------------- AddRemoveLayersProperties ---------------------- */

class FLOW_DOCUMENT_API AddRemoveLayersProperties : public pillar::Command {
 public:
  explicit AddRemoveLayersProperties(QString name, FlowDocument* document,
                                     QList<Layer*> layers,
                                     QVariantMap properties,
                                     Command* parent = nullptr);
  ~AddRemoveLayersProperties() override;

 protected:
  void addProperties();
  void removeProperties();

 protected:
  FlowDocument* m_document;
  QList<Layer*> m_layers;
  QVariantMap m_properties;
};

/* ---------------------------- AddLayersProperties ------------------------- */

class FLOW_DOCUMENT_API AddLayersProperties : public AddRemoveLayersProperties {
 public:
  explicit AddLayersProperties(FlowDocument* document, QList<Layer*> layers,
                               QVariantMap properties,
                               Command* parent = nullptr);
  ~AddLayersProperties() override;

  void undo() override;
  void redo() override;
};

/* --------------------------- RemoveLayersProperties ----------------------- */

class FLOW_DOCUMENT_API RemoveLayersProperties
    : public AddRemoveLayersProperties {
 public:
  explicit RemoveLayersProperties(FlowDocument* document, QList<Layer*> layers,
                                  QStringList properties,
                                  Command* parent = nullptr);
  ~RemoveLayersProperties() override;

  void undo() override;
  void redo() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CHANGE_LAYER_H