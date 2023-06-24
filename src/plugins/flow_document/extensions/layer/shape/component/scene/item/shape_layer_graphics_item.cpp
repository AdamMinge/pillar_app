/* ----------------------------------- Local -------------------------------- */
#include "component/scene/item/shape_layer_graphics_item.h"

#include "flow/shape_layer.h"
/* -------------------------------------------------------------------------- */

ShapeLayerGraphicsItem::ShapeLayerGraphicsItem(
    ShapeLayer* layer, flow_document::FlowDocument* document,
    QGraphicsItem* parent)
    : flow_document::LayerGraphicsItem(layer, document, parent) {}

ShapeLayerGraphicsItem::~ShapeLayerGraphicsItem() = default;

ShapeLayer* ShapeLayerGraphicsItem::getShapeLayer() const {
  return static_cast<ShapeLayer*>(getObject());
}

void ShapeLayerGraphicsItem::onEvent(const flow_document::ChangeEvent& event) {}
