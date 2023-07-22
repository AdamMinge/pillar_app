/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/layer_item.h"

#include "flow_document/component/scene/item/factory/item_factory.h"
#include "flow_document/component/scene/item/node_item.h"
#include "flow_document/event/change_event.h"
#include "flow_document/event/layer_change_event.h"
#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/connection_layer.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/node.h"
#include "flow_document/flow/node_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------------- LayerItem ------------------------------ */

LayerItem::LayerItem(Layer* layer, FlowDocument* document,
                     QGraphicsItem* parent)
    : ObjectItem(layer, document, parent) {
  setPos(getLayer()->getPosition());
  setVisible(getLayer()->isVisible());
}

LayerItem::~LayerItem() = default;

Layer* LayerItem::getLayer() const { return static_cast<Layer*>(getObject()); }

void LayerItem::onEvent(const ChangeEvent& event) {
  if (event.getType() == LayersChangeEvent::type) {
    const auto& layer_event = static_cast<const LayersChangeEvent&>(event);
    if (layer_event.contains(getLayer())) onUpdate(layer_event);
  }
}

void LayerItem::onUpdate(const LayersChangeEvent& event) {
  const auto layer = getLayer();
  const auto properties = event.getProperties();

  using enum LayersChangeEvent::Property;
  if (properties & Visible) {
    setVisible(layer->isVisible());
  }
  if (properties & Locked) {
    // TODO
  }
  if (properties & Opacity) {
    setOpacity(layer->getOpacity());
  }
  if (properties & Position) {
    setPos(layer->getPosition());
  }
}

/* -------------------------- GroupLayerItem ------------------------ */

GroupLayerItem::GroupLayerItem(GroupLayer* layer, FlowDocument* document,
                               QGraphicsItem* parent)
    : LayerItem(layer, document, parent) {
  for (auto& layer : *getGroupLayer()) {
    m_layer_items.append(
        createItem<LayerItem>(layer.get(), getDocument(), this));
  }
}

GroupLayerItem::~GroupLayerItem() = default;

GroupLayer* GroupLayerItem::getGroupLayer() const {
  return static_cast<GroupLayer*>(getObject());
}

void GroupLayerItem::onEvent(const ChangeEvent& event) {
  LayerItem::onEvent(event);

  if (event.getType() == LayerEvent::type) {
    const auto& layer_event = static_cast<const LayerEvent&>(event);
    switch (layer_event.getEvent()) {
      using enum LayerEvent::Event;

      case Added: {
        if (getGroupLayer() == layer_event.getGroupLayer()) {
          auto layer = layer_event.getGroupLayer()->at(layer_event.getIndex());

          m_layer_items.insert(
              layer_event.getIndex(),
              createItem<LayerItem>(layer, getDocument(), this));
        }

        break;
      }

      case Removed: {
        if (getGroupLayer() == layer_event.getGroupLayer()) {
          auto item = m_layer_items.takeAt(layer_event.getIndex());
          item->deleteLater();
        }

        break;
      }
    }
  }
}

/* --------------------------- NodeLayerItem ------------------------ */

NodeLayerItem::NodeLayerItem(NodeLayer* layer, FlowDocument* document,
                             QGraphicsItem* parent)
    : LayerItem(layer, document, parent) {
  for (auto& node : *getNodeLayer()) {
    m_node_items.append(createItem<NodeItem>(node.get(), getDocument(), this));
  }
}

NodeLayerItem::~NodeLayerItem() = default;

NodeLayer* NodeLayerItem::getNodeLayer() const {
  return static_cast<NodeLayer*>(getObject());
}

void NodeLayerItem::onEvent(const ChangeEvent& event) {
  LayerItem::onEvent(event);

  if (event.getType() == NodeEvent::type) {
    const auto& node_event = static_cast<const NodeEvent&>(event);
    switch (node_event.getEvent()) {
      using enum NodeEvent::Event;

      case Added: {
        if (getNodeLayer() == node_event.getNodeLayer()) {
          auto node = node_event.getNodeLayer()->at(node_event.getIndex());

          m_node_items.insert(node_event.getIndex(),
                              createItem<NodeItem>(node, getDocument(), this));
        }

        break;
      }

      case Removed: {
        if (getNodeLayer() == node_event.getNodeLayer()) {
          auto item = m_node_items.takeAt(node_event.getIndex());
          item->deleteLater();
        }

        break;
      }
    }
  }

  for (auto i = 0; i < m_node_items.size(); ++i) {
    m_node_items[i]->setZValue(i);
  }
}

/* --------------------------- ConnectionLayerItem -------------------------- */

ConnectionLayerItem::ConnectionLayerItem(ConnectionLayer* layer,
                                         FlowDocument* document,
                                         QGraphicsItem* parent)
    : LayerItem(layer, document, parent) {}

ConnectionLayerItem::~ConnectionLayerItem() = default;

ConnectionLayer* ConnectionLayerItem::getConnectionLayer() const {
  return static_cast<ConnectionLayer*>(getObject());
}

void ConnectionLayerItem::onEvent(const ChangeEvent& event) {
  LayerItem::onEvent(event);
}

}  // namespace flow_document