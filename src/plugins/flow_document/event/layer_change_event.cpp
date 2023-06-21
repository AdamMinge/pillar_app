/* ----------------------------------- Local -------------------------------- */
#include "flow_document/event/layer_change_event.h"

#include "flow_document/flow/group_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------------- LayerEvent ----------------------------- */

LayerEvent::LayerEvent(Type type, GroupLayer* group_layer, qsizetype index)
    : ChangeEvent(type), m_group_layer(group_layer), m_index(index) {}

LayerEvent::~LayerEvent() = default;

GroupLayer* LayerEvent::getGroupLayer() const { return m_group_layer; }

qsizetype LayerEvent::getIndex() const { return m_index; }

/* ------------------------------ LayersChangeEvent ------------------------- */

LayersEvent::LayersEvent(Type type, QList<Layer*> layers)
    : ChangeEvent(type), m_layers(std::move(layers)) {}
LayersEvent::~LayersEvent() = default;

const QList<Layer*>& LayersEvent::getLayers() const { return m_layers; }

/* ------------------------------ LayersChangeEvent ------------------------- */

LayersChangeEvent::LayersChangeEvent(QList<Layer*> layers,
                                     Properties properties)
    : LayersEvent(Type::LayersChanged, std::move(layers)),
      m_properties(properties) {}

LayersChangeEvent::~LayersChangeEvent() = default;

LayersChangeEvent::Properties LayersChangeEvent::getProperties() const {
  return m_properties;
}

}  // namespace flow_document
