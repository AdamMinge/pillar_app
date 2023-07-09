#ifndef SHAPE_ITEM_H
#define SHAPE_ITEM_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/scene/item/object_item.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class Shape;

class SHAPE_API ShapeItem : public flow_document::ObjectItem {
  Q_OBJECT

 public:
  explicit ShapeItem(Shape* shape, flow_document::FlowDocument* document,
                     QGraphicsItem* parent = nullptr);
  ~ShapeItem() override;

  [[nodiscard]] Shape* getShape() const;

 private Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent& event) override;
};

#endif  // SHAPE_ITEM_H
