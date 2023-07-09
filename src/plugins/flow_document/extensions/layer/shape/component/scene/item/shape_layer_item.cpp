/* ----------------------------------- Local -------------------------------- */
#include "component/scene/item/shape_layer_item.h"

#include "flow/shape_layer.h"
/* -------------------------------------------------------------------------- */

ShapeLayerItem::ShapeLayerItem(ShapeLayer* layer,
                               flow_document::FlowDocument* document,
                               QGraphicsItem* parent)
    : flow_document::LayerItem(layer, document, parent) {}

ShapeLayerItem::~ShapeLayerItem() = default;

ShapeLayer* ShapeLayerItem::getShapeLayer() const {
  return static_cast<ShapeLayer*>(getObject());
}

void ShapeLayerItem::onEvent(const flow_document::ChangeEvent& event) {}
