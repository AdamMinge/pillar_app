/* ----------------------------------- Local -------------------------------- */
#include "flow_document/event/layer_change_event.h"

#include "flow_document/flow/group_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------------- LayerEvent ----------------------------- */

LayerEvent::LayerEvent(Event event, GroupLayer* group_layer, qsizetype index)
    : ChangeEvent(type),
      m_event(event),
      m_group_layer(group_layer),
      m_index(index) {}

LayerEvent::~LayerEvent() = default;

LayerEvent::Event LayerEvent::getEvent() const { return m_event; }

GroupLayer* LayerEvent::getGroupLayer() const { return m_group_layer; }

qsizetype LayerEvent::getIndex() const { return m_index; }

/* ------------------------------ LayersChangeEvent ------------------------- */

LayersChangeEvent::LayersChangeEvent(QList<Layer*> layers,
                                     Properties properties)
    : ChangeEvent(type),
      m_layers(std::move(layers)),
      m_properties(properties) {}

LayersChangeEvent::~LayersChangeEvent() = default;

const QList<Layer*>& LayersChangeEvent::getLayers() const { return m_layers; }

LayersChangeEvent::Properties LayersChangeEvent::getProperties() const {
  return m_properties;
}

}  // namespace flow_document
