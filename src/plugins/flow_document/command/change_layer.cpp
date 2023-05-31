/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/change_layer.h"

#include "flow_document/event/layer_change_event.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow_document.h"
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

}  // namespace flow_document
