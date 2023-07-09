/* ----------------------------------- Local -------------------------------- */
#include "component/scene/item/shape_item.h"

#include "flow/shape.h"
/* -------------------------------------------------------------------------- */

ShapeItem::ShapeItem(Shape* shape, flow_document::FlowDocument* document,
                     QGraphicsItem* parent)
    : flow_document::ObjectItem(shape, document, parent) {}

ShapeItem::~ShapeItem() = default;

Shape* ShapeItem::getShape() const { return static_cast<Shape*>(getObject()); }

void ShapeItem::onEvent(const flow_document::ChangeEvent& event) {}