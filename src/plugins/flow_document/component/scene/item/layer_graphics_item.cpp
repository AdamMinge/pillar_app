/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/layer_graphics_item.h"

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
    : GraphicsItem(layer, document, parent) {}

LayerGraphicsItem::~LayerGraphicsItem() = default;

Layer* LayerGraphicsItem::getLayer() const {
  return static_cast<Layer*>(getObject());
}

void LayerGraphicsItem::onEvent(const ChangeEvent& event) {
  switch (event.getType()) {}
}

/* -------------------------- GroupLayerGraphicsItem ------------------------ */

GroupLayerGraphicsItem::GroupLayerGraphicsItem(GroupLayer* layer,
                                               FlowDocument* document,
                                               QGraphicsItem* parent)
    : LayerGraphicsItem(layer, document, parent) {}

GroupLayerGraphicsItem::~GroupLayerGraphicsItem() = default;

GroupLayer* GroupLayerGraphicsItem::getGroupLayer() const {
  return static_cast<GroupLayer*>(getObject());
}

void GroupLayerGraphicsItem::onEvent(const ChangeEvent& event) {
  switch (event.getType()) {
    case ChangeEvent::Type::LayerAdded: {
      const auto& e = static_cast<const LayerEvent&>(event);
      if (getGroupLayer() == e.getGroupLayer()) {
        auto layer = e.getGroupLayer()->at(e.getIndex());

        m_layer_items.insert(
            e.getIndex(), creatItem<LayerGraphicsItem>(layer, getDocument()));
      }

      break;
    }

    case ChangeEvent::Type::LayerRemoved: {
      const auto& e = static_cast<const LayerEvent&>(event);
      if (getGroupLayer() == e.getGroupLayer()) {
        auto item = m_layer_items.takeAt(e.getIndex());
        item->deleteLater();
      }

      break;
    }
  }
}

/* --------------------------- NodeLayerGraphicsItem ------------------------ */

NodeLayerGraphicsItem::NodeLayerGraphicsItem(NodeLayer* layer,
                                             FlowDocument* document,
                                             QGraphicsItem* parent)
    : LayerGraphicsItem(layer, document, parent) {}

NodeLayerGraphicsItem::~NodeLayerGraphicsItem() = default;

NodeLayer* NodeLayerGraphicsItem::getNodeLayer() const {
  return static_cast<NodeLayer*>(getObject());
}

void NodeLayerGraphicsItem::onEvent(const ChangeEvent& event) {
  switch (event.getType()) {
    case ChangeEvent::Type::NodeAdded: {
      const auto& e = static_cast<const NodeEvent&>(event);
      if (getNodeLayer() == e.getNodeLayer()) {
        auto node = e.getNodeLayer()->at(e.getIndex());

        m_node_items.insert(e.getIndex(),
                            creatItem<NodeGraphicsItem>(node, getDocument()));
      }

      break;
    }

    case ChangeEvent::Type::NodeRemoved: {
      const auto& e = static_cast<const NodeEvent&>(event);
      if (getNodeLayer() == e.getNodeLayer()) {
        auto item = m_node_items.takeAt(e.getIndex());
        item->deleteLater();
      }

      break;
    }
  }
}

}  // namespace flow_document