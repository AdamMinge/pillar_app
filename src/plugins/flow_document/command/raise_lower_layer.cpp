/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/raise_lower_layer.h"

#include "flow_document/event/layer_change_event.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------- RaiseLowerLayers --------------------------- */

RaiseLowerLayers::RaiseLowerLayers(const QString& name, FlowDocument* document,
                                   QList<Layer*> layers, Command* parent)
    : egnite::Command(name, parent),
      m_document(document),
      m_layers(std::move(layers)) {
  std::sort(m_layers.begin(), m_layers.end(),
            [](const auto& left, const auto& right) {
              return getLayerHierarchicalId(left) <
                     getLayerHierarchicalId(right);
            });
}

RaiseLowerLayers::~RaiseLowerLayers() = default;

void RaiseLowerLayers::raiseLayers() { moveLayers(true); }

void RaiseLowerLayers::lowerLayers() { moveLayers(false); }

void RaiseLowerLayers::moveLayers(bool raise) {
  auto current_layer = m_document->getCurrentLayer();
  auto selected_layers = m_document->getSelectedLayers();

  auto process_layer = [this, raise](Layer* layer) {
    const auto step = raise ? 1 : -1;
    const auto parent = layer->getParent();
    const auto index = parent->indexOf(layer);
    const auto can_move = raise ? index < parent->size() - 1 : index > 0;

    auto new_parent = static_cast<GroupLayer*>(nullptr);
    auto new_index = 0;

    if (can_move) {
      auto next_layer = parent->at(index + step);
      if (next_layer->isClassOrChild<GroupLayer>()) {
        new_parent = static_cast<GroupLayer*>(next_layer);
        new_index = raise ? 0 : new_parent->size();
      } else {
        new_parent = parent;
        new_index = index + step;
      }
    } else {
      new_parent = parent->getParent();
      new_index = new_parent->indexOf(parent) + (raise ? 1 : 0);
    }

    this->moveLayer(layer, new_parent, new_index);
  };

  if (raise) {
    std::for_each(m_layers.begin(), m_layers.end(), process_layer);
  } else {
    std::for_each(m_layers.rbegin(), m_layers.rend(), process_layer);
  }

  m_document->setCurrentLayer(current_layer);
  m_document->setSelectedLayers(selected_layers);
}

void RaiseLowerLayers::moveLayer(Layer* layer, GroupLayer* parent,
                                 qsizetype index) {
  auto from_parent = layer->getParent();
  auto from_index = from_parent->indexOf(layer);

  Q_EMIT m_document->event(
      LayerEvent(LayerEvent::Event::AboutToBeRemoved, from_parent, from_index));
  auto reparent_layer = from_parent->take(from_index);
  Q_ASSERT(reparent_layer);
  Q_EMIT m_document->event(
      LayerEvent(LayerEvent::Event::Removed, from_parent, from_index));

  Q_EMIT m_document->event(
      LayerEvent(LayerEvent::Event::AboutToBeAdded, parent, index));
  parent->insert(index, std::move(reparent_layer));
  Q_EMIT m_document->event(LayerEvent(LayerEvent::Event::Added, parent, index));
}

/* -------------------------------- RaiseLayers ----------------------------- */

RaiseLayers::RaiseLayers(FlowDocument* document, QList<Layer*> layers,
                         Command* parent)
    : RaiseLowerLayers(QLatin1String("RaiseLayers"), document,
                       std::move(layers), parent) {
  const auto command_text =
      QObject::tr("Raise Layer(s)", nullptr, m_layers.size());
  setText(command_text);
}

RaiseLayers::~RaiseLayers() = default;

void RaiseLayers::undo() { lowerLayers(); }

void RaiseLayers::redo() { raiseLayers(); }

/* -------------------------------- LowerLayers ----------------------------- */

LowerLayers::LowerLayers(FlowDocument* document, QList<Layer*> layers,
                         Command* parent)
    : RaiseLowerLayers(QLatin1String("LowerLayers"), document,
                       std::move(layers), parent) {
  const auto command_text =
      QObject::tr("Lower Layer(s)", nullptr, m_layers.size());
  setText(command_text);
}

LowerLayers::~LowerLayers() = default;

void LowerLayers::undo() { raiseLayers(); }

void LowerLayers::redo() { lowerLayers(); }

}  // namespace flow_document
