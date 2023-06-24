/* ----------------------------------- Local -------------------------------- */
#include "component/scene/item/shape_graphics_item.h"

#include "flow/shape.h"
/* -------------------------------------------------------------------------- */

ShapeGraphicsItem::ShapeGraphicsItem(Shape* shape,
                                     flow_document::FlowDocument* document,
                                     QGraphicsItem* parent)
    : flow_document::GraphicsItem(shape, document, parent) {}

ShapeGraphicsItem::~ShapeGraphicsItem() = default;

Shape* ShapeGraphicsItem::getShape() const {
  return static_cast<Shape*>(getObject());
}

void ShapeGraphicsItem::onEvent(const flow_document::ChangeEvent& event) {}