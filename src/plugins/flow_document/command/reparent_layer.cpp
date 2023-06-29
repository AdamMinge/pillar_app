/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/reparent_layer.h"

#include "flow_document/event/layer_change_event.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

ReparentLayers::ReparentLayers(FlowDocument* document, QVector<Layer*> layers,
                               GroupLayer* group_layer, qsizetype index,
                               Command* parent)
    : egnite::Command(QLatin1String("ReparentLayers"), parent),
      m_document(document) {
  for (auto layer : layers) {
    Q_ASSERT(layer != group_layer);
    m_reparent_data.push_back(ReparentData{layer, group_layer, index});
  }

  m_reparent_data.sort([](const auto& left, const auto& right) {
    return getLayerHierarchicalId(left.layer) <
           getLayerHierarchicalId(right.layer);
  });

  const auto command_text =
      QObject::tr("Reparent Layer(s)", nullptr, m_reparent_data.size());
  setText(command_text);
}

ReparentLayers::~ReparentLayers() = default;

void ReparentLayers::undo() { reparentLayers(true); }

void ReparentLayers::redo() { reparentLayers(false); }

void ReparentLayers::reparentLayers(bool revert) {
  auto current_layer = m_document->getCurrentLayer();
  auto selected_layers = m_document->getSelectedLayers();

  auto process_reparent_data =
      std::bind(&ReparentLayers::reparentLayer, this, std::placeholders::_1);
  if (revert) {
    std::for_each(m_reparent_data.begin(), m_reparent_data.end(),
                  process_reparent_data);
  } else {
    std::for_each(m_reparent_data.rbegin(), m_reparent_data.rend(),
                  process_reparent_data);
  }

  m_document->setCurrentLayer(current_layer);
  m_document->setSelectedLayers(selected_layers);
}

void ReparentLayers::reparentLayer(ReparentData& data) {
  auto current_parent = data.layer->getParent();
  Q_ASSERT(current_parent);
  auto current_index = current_parent->indexOf(data.layer);
  Q_ASSERT(current_index >= 0);

  Q_EMIT m_document->event(LayerEvent(LayerEvent::Event::AboutToBeRemoved,
                                      current_parent, current_index));
  auto reparent_layer = current_parent->take(current_index);
  Q_ASSERT(reparent_layer);
  Q_EMIT m_document->event(
      LayerEvent(LayerEvent::Event::Removed, current_parent, current_index));

  auto same_parent = current_parent == data.parent;
  if (same_parent && current_index < data.index) {
    data.index -= 1;
  } else if (same_parent && current_index > data.index) {
    current_index += 1;
  }

  Q_EMIT m_document->event(
      LayerEvent(LayerEvent::Event::AboutToBeAdded, data.parent, data.index));
  data.parent->insert(data.index, std::move(reparent_layer));
  Q_EMIT m_document->event(
      LayerEvent(LayerEvent::Event::Added, data.parent, data.index));

  data.parent = current_parent;
  data.index =
      std::min(current_index, std::max(current_parent->size(), qsizetype(0)));
}

}  // namespace flow_document
