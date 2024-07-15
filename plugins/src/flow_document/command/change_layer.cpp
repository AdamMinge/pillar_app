/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/change_layer.h"

#include "flow_document/event/layer_change_event.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow_document.h"
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/container/map.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------------ SetLayersVisible -------------------------- */

SetLayersVisible::SetLayersVisible(FlowDocument* document, QList<Layer*> layers,
                                   bool visible, Command* parent)
    : ChangeValue<Layer, bool>(QLatin1String("SetLayersVisible"), document,
                               std::move(layers), visible, parent) {
  const auto what = QObject::tr("Set Layer(s)", nullptr, getObjects().size());
  const auto action =
      visible ? QObject::tr("Visible") : QObject::tr("Invisible");

  setText(QString("%1 %2").arg(what, action));
}

SetLayersVisible::~SetLayersVisible() = default;

bool SetLayersVisible::getValue(const Layer* layer) const {
  return layer->isVisible();
}

void SetLayersVisible::setValue(Layer* layer, const bool& visible) {
  layer->setVisible(visible);
  getDocument()->event(
      LayersChangeEvent({layer}, LayersChangeEvent::Property::Visible));
}

/* ------------------------------ SetLayersLocked --------------------------- */

SetLayersLocked::SetLayersLocked(FlowDocument* document, QList<Layer*> layers,
                                 bool locked, Command* parent)
    : ChangeValue<Layer, bool>(QLatin1String("SetLayersLocked"), document,
                               std::move(layers), locked, parent) {
  const auto what = QObject::tr("Set Layer(s)", nullptr, getObjects().size());
  const auto action = locked ? QObject::tr("Locked") : QObject::tr("Unlocked");

  setText(QString("%1 %2").arg(what, action));
}

SetLayersLocked::~SetLayersLocked() = default;

bool SetLayersLocked::getValue(const Layer* layer) const {
  return layer->isLocked();
}

void SetLayersLocked::setValue(Layer* layer, const bool& locked) {
  layer->setLocked(locked);
  getDocument()->event(
      LayersChangeEvent({layer}, LayersChangeEvent::Property::Locked));
}

/* ------------------------------- SetLayersName ---------------------------- */

SetLayersName::SetLayersName(FlowDocument* document, QList<Layer*> layers,
                             QString name, Command* parent)
    : ChangeValue<Layer, QString>(QLatin1String("SetLayersName"), document,
                                  std::move(layers), name, parent) {
  const auto what = QObject::tr("Set Layer(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Name");
  setText(QString("%1 %2").arg(what, action));
}

SetLayersName::~SetLayersName() = default;

QString SetLayersName::getValue(const Layer* layer) const {
  return layer->getName();
}

void SetLayersName::setValue(Layer* layer, const QString& name) {
  layer->setName(name);
  getDocument()->event(
      LayersChangeEvent({layer}, LayersChangeEvent::Property::Name));
}

/* ------------------------------ SetLayersOpacity -------------------------- */

SetLayersOpacity::SetLayersOpacity(FlowDocument* document, QList<Layer*> layers,
                                   qreal opacity, Command* parent)
    : ChangeValue<Layer, qreal>(QLatin1String("SetLayersOpacity"), document,
                                std::move(layers), opacity, parent) {
  const auto what = QObject::tr("Set Layer(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Opacity");
  setText(QString("%1 %2").arg(what, action));
}

SetLayersOpacity::~SetLayersOpacity() = default;

qreal SetLayersOpacity::getValue(const Layer* layer) const {
  return layer->getOpacity();
}

void SetLayersOpacity::setValue(Layer* layer, const qreal& opacity) {
  layer->setOpacity(opacity);
  getDocument()->event(
      LayersChangeEvent({layer}, LayersChangeEvent::Property::Opacity));
}

/* ----------------------------- SetLayersPosition -------------------------- */

SetLayersPosition::SetLayersPosition(FlowDocument* document,
                                     QList<Layer*> layers, QPointF position,
                                     Command* parent)
    : ChangeValue<Layer, QPointF>(QLatin1String("SetLayersPosition"), document,
                                  std::move(layers), position, parent) {
  const auto what = QObject::tr("Set Layer(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Position");
  setText(QString("%1 %2").arg(what, action));
}

SetLayersPosition::~SetLayersPosition() = default;

QPointF SetLayersPosition::getValue(const Layer* layer) const {
  return layer->getPosition();
}

void SetLayersPosition::setValue(Layer* layer, const QPointF& position) {
  layer->setPosition(position);
  getDocument()->event(
      LayersChangeEvent({layer}, LayersChangeEvent::Property::Position));
}

/* -------------------------- SetLayersCustomProperty ----------------------- */

SetLayersCustomProperty::SetLayersCustomProperty(FlowDocument* document,
                                                 QList<Layer*> layers,
                                                 QString property,
                                                 QVariant value,
                                                 Command* parent)
    : ChangeValue<Layer, QVariant>(
          QString("SetLayersCustomProperty-%1").arg(property), document,
          std::move(layers), std::move(value), parent),
      m_property(std::move(property)) {
  const auto what = QObject::tr("Set Layer(s)", nullptr, getObjects().size());
  const auto action = QObject::tr("Custom Property");
  setText(QString("%1 %2").arg(what, action));
}

SetLayersCustomProperty::~SetLayersCustomProperty() = default;

QVariant SetLayersCustomProperty::getValue(const Layer* layer) const {
  return layer->getProperty(m_property);
}

void SetLayersCustomProperty::setValue(Layer* layer, const QVariant& value) {
  layer->setProperty(m_property, value);
  getDocument()->event(
      LayersChangeEvent({layer}, LayersChangeEvent::Property::Custom));
}

/* ------------------------- AddRemoveLayersProperties ---------------------- */

AddRemoveLayersProperties::AddRemoveLayersProperties(QString name,
                                                     FlowDocument* document,
                                                     QList<Layer*> layers,
                                                     QVariantMap properties,
                                                     Command* parent)
    : egnite::Command(name, parent),
      m_document(document),
      m_layers(std::move(layers)),
      m_properties(std::move(properties)) {}

AddRemoveLayersProperties::~AddRemoveLayersProperties() = default;

void AddRemoveLayersProperties::addProperties() {
  for (auto layer : m_layers) {
    auto& old_properties = layer->getProperties();
    auto new_properties = old_properties;
    new_properties.insert(m_properties);

    Q_ASSERT(new_properties.size() ==
             old_properties.size() + m_properties.size());

    layer->setProperties(new_properties);

    m_document->event(
        LayersChangeEvent({layer}, LayersChangeEvent::Property::Custom));
  }
}

void AddRemoveLayersProperties::removeProperties() {
  for (auto layer : m_layers) {
    auto& old_properties = layer->getProperties();

    auto new_properties = old_properties;
    for (auto key : m_properties.keys()) {
      Q_ASSERT(old_properties.contains(key));
      m_properties[key] = old_properties[key];

      new_properties.remove(key);
    }

    layer->setProperties(new_properties);

    m_document->event(
        LayersChangeEvent({layer}, LayersChangeEvent::Property::Custom));
  }
}

/* ---------------------------- AddLayersProperties ------------------------- */

AddLayersProperties::AddLayersProperties(FlowDocument* document,
                                         QList<Layer*> layers,
                                         QVariantMap properties,
                                         Command* parent)
    : AddRemoveLayersProperties(QLatin1String("AddLayersProperties"), document,
                                std::move(layers), std::move(properties)) {
  const auto what =
      QObject::tr("Add Custom Property(s)", nullptr, m_properties.size());
  setText(what);
}

AddLayersProperties::~AddLayersProperties() = default;

void AddLayersProperties::undo() { removeProperties(); }

void AddLayersProperties::redo() { addProperties(); }

/* --------------------------- RemoveLayersProperties ----------------------- */

RemoveLayersProperties::RemoveLayersProperties(FlowDocument* document,
                                               QList<Layer*> layers,
                                               QStringList properties,
                                               Command* parent)
    : AddRemoveLayersProperties(QLatin1String("RemoveLayersProperties"),
                                document, std::move(layers),
                                qtils::mapFromKeys(properties, QVariant{})) {
  const auto what =
      QObject::tr("Remove Custom Property(s)", nullptr, m_properties.size());
  setText(what);
}

RemoveLayersProperties::~RemoveLayersProperties() = default;

void RemoveLayersProperties::undo() { addProperties(); }

void RemoveLayersProperties::redo() { removeProperties(); }

}  // namespace flow_document
