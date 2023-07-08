/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/layer_graphics_item.h"

#include "flow_document/component/scene/item/factory/graphics_item_factory.h"
#include "flow_document/component/scene/item/node_graphics_item.h"
#include "flow_document/event/change_event.h"
#include "flow_document/event/layer_change_event.h"
#include "flow_document/event/node_change_event.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/node.h"
#include "flow_document/flow/node_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------- LayerGraphicsItem -------------------------- */

LayerGraphicsItem::LayerGraphicsItem(Layer* layer, FlowDocument* document,
                                     QGraphicsItem* parent)
    : ObjectGraphicsItem(layer, document, parent) {}

LayerGraphicsItem::~LayerGraphicsItem() = default;

Layer* LayerGraphicsItem::getLayer() const {
  return static_cast<Layer*>(getObject());
}

void LayerGraphicsItem::onEvent(const ChangeEvent& event) {
  if (event.getType() == LayersChangeEvent::type) {
    const auto& layer_event = static_cast<const LayersChangeEvent&>(event);
    if (layer_event.contains(getLayer())) onUpdate(layer_event);
  }
}

void LayerGraphicsItem::onUpdate(const LayersChangeEvent& event) {
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

/* -------------------------- GroupLayerGraphicsItem ------------------------ */

GroupLayerGraphicsItem::GroupLayerGraphicsItem(GroupLayer* layer,
                                               FlowDocument* document,
                                               QGraphicsItem* parent)
    : LayerGraphicsItem(layer, document, parent) {
  for (auto& layer : *getGroupLayer()) {
    m_layer_items.append(createGraphicsItem<LayerGraphicsItem>(
        layer.get(), getDocument(), this));
  }
}

GroupLayerGraphicsItem::~GroupLayerGraphicsItem() = default;

GroupLayer* GroupLayerGraphicsItem::getGroupLayer() const {
  return static_cast<GroupLayer*>(getObject());
}

void GroupLayerGraphicsItem::onEvent(const ChangeEvent& event) {
  LayerGraphicsItem::onEvent(event);

  if (event.getType() == LayerEvent::type) {
    const auto& layer_event = static_cast<const LayerEvent&>(event);
    switch (layer_event.getEvent()) {
      using enum LayerEvent::Event;

      case Added: {
        if (getGroupLayer() == layer_event.getGroupLayer()) {
          auto layer = layer_event.getGroupLayer()->at(layer_event.getIndex());

          m_layer_items.insert(layer_event.getIndex(),
                               createGraphicsItem<LayerGraphicsItem>(
                                   layer, getDocument(), this));
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

/* --------------------------- NodeLayerGraphicsItem ------------------------ */

NodeLayerGraphicsItem::NodeLayerGraphicsItem(NodeLayer* layer,
                                             FlowDocument* document,
                                             QGraphicsItem* parent)
    : LayerGraphicsItem(layer, document, parent) {
  for (auto& node : *getNodeLayer()) {
    m_node_items.append(
        createGraphicsItem<NodeGraphicsItem>(node.get(), getDocument(), this));
  }
}

NodeLayerGraphicsItem::~NodeLayerGraphicsItem() = default;

NodeLayer* NodeLayerGraphicsItem::getNodeLayer() const {
  return static_cast<NodeLayer*>(getObject());
}

void NodeLayerGraphicsItem::onEvent(const ChangeEvent& event) {
  LayerGraphicsItem::onEvent(event);

  if (event.getType() == NodeEvent::type) {
    const auto& node_event = static_cast<const NodeEvent&>(event);
    switch (node_event.getEvent()) {
      using enum NodeEvent::Event;

      case Added: {
        if (getNodeLayer() == node_event.getNodeLayer()) {
          auto node = node_event.getNodeLayer()->at(node_event.getIndex());

          m_node_items.insert(
              node_event.getIndex(),
              createGraphicsItem<NodeGraphicsItem>(node, getDocument(), this));
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
}

}  // namespace flow_document