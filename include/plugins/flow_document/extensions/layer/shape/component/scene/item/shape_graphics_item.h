#ifndef SHAPE_GRAPHICS_ITEM_H
#define SHAPE_GRAPHICS_ITEM_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/scene/item/object_graphics_item.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class Shape;

class SHAPE_API ShapeGraphicsItem : public flow_document::ObjectGraphicsItem {
  Q_OBJECT

 public:
  explicit ShapeGraphicsItem(Shape* shape,
                             flow_document::FlowDocument* document,
                             QGraphicsItem* parent = nullptr);
  ~ShapeGraphicsItem() override;

  [[nodiscard]] Shape* getShape() const;

 private Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent& event) override;
};

#endif  // SHAPE_GRAPHICS_ITEM_H
