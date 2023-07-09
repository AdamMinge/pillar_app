#ifndef SHAPE_LAYER_ITEM_H
#define SHAPE_LAYER_ITEM_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/scene/item/layer_item.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class ShapeItem;
class ShapeLayer;

class SHAPE_API ShapeLayerItem : public flow_document::LayerItem {
  Q_OBJECT

 public:
  explicit ShapeLayerItem(ShapeLayer* layer,
                          flow_document::FlowDocument* document,
                          QGraphicsItem* parent = nullptr);
  ~ShapeLayerItem() override;

  [[nodiscard]] ShapeLayer* getShapeLayer() const;

 private Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent& event) override;

 private:
  QList<ShapeItem*> m_shape_items;
};

#endif  // SHAPE_LAYER_ITEM_H
