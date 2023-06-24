#ifndef SHAPE_LAYER_GRAPHICS_ITEM_H
#define SHAPE_LAYER_GRAPHICS_ITEM_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/scene/item/layer_graphics_item.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class ShapeGraphicsItem;
class ShapeLayer;

class SHAPE_API ShapeLayerGraphicsItem
    : public flow_document::LayerGraphicsItem {
  Q_OBJECT

 public:
  explicit ShapeLayerGraphicsItem(ShapeLayer* layer,
                                  flow_document::FlowDocument* document,
                                  QGraphicsItem* parent = nullptr);
  ~ShapeLayerGraphicsItem() override;

  [[nodiscard]] ShapeLayer* getShapeLayer() const;

 private Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent& event) override;

 private:
  QList<ShapeGraphicsItem*> m_shape_items;
};

#endif  // SHAPE_LAYER_GRAPHICS_ITEM_H
