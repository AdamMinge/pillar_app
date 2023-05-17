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
    : egnite::Command(QLatin1String("SetLayersVisible"), parent),
      m_document(document),
      m_layers(std::move(layers)),
      m_visible(visible) {
  const auto what = m_layers.size() > 1 ? QObject::tr("Set Layers")
                                        : QObject::tr("Set Layer");
  const auto action =
      m_visible ? QObject::tr("Visible") : QObject::tr("Invisible");

  setText(QString("%1 %2").arg(what, action));
}

SetLayersVisible::~SetLayersVisible() = default;

void SetLayersVisible::undo() { setVisible(!m_visible); }

void SetLayersVisible::redo() { setVisible(m_visible); }

void SetLayersVisible::setVisible(bool visible) {
  for (auto layer : m_layers) layer->setVisible(visible);

  m_document->event(
      LayersChangeEvent(m_layers, LayersChangeEvent::Property::Visible));
}

/* ------------------------------ SetLayersLocked --------------------------- */

SetLayersLocked::SetLayersLocked(FlowDocument* document, QList<Layer*> layers,
                                 bool locked, Command* parent)
    : egnite::Command(QLatin1String("SetLayersLocked"), parent),
      m_document(document),
      m_layers(std::move(layers)),
      m_locked(locked) {
  const auto what = m_layers.size() > 1 ? QObject::tr("Set Layers")
                                        : QObject::tr("Set Layer");
  const auto action =
      m_locked ? QObject::tr("Locked") : QObject::tr("Unlocked");

  setText(QString("%1 %2").arg(what, action));
}

SetLayersLocked::~SetLayersLocked() = default;

void SetLayersLocked::undo() { setLocked(!m_locked); }

void SetLayersLocked::redo() { setLocked(m_locked); }

void SetLayersLocked::setLocked(bool locked) {
  for (auto layer : m_layers) layer->setLocked(locked);

  m_document->event(
      LayersChangeEvent(m_layers, LayersChangeEvent::Property::Locked));
}

/* ------------------------------- SetLayerName ----------------------------- */

SetLayerName::SetLayerName(FlowDocument* document, Layer* layer, QString name,
                           Command* parent)
    : egnite::Command(QLatin1String("SetLayerName"), parent),
      m_document(document),
      m_layer(layer),
      m_name(std::move(name)) {
  setText(QObject::tr("Set Layer Name"));
}

SetLayerName::~SetLayerName() = default;

void SetLayerName::undo() { setName(); }

void SetLayerName::redo() { setName(); }

void SetLayerName::setName() {
  auto old_name = m_layer->getName();
  m_layer->setName(m_name);
  m_name = old_name;

  m_document->event(
      LayersChangeEvent({m_layer}, LayersChangeEvent::Property::Name));
}

}  // namespace flow_document
