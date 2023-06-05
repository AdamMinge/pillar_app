#ifndef FLOW_DOCUMENT_LAYER_GRAPHICS_ITEM_H
#define FLOW_DOCUMENT_LAYER_GRAPHICS_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/graphics_item.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API LayerGraphicsItem : public GraphicsItem {
  Q_OBJECT

 public:
  explicit LayerGraphicsItem(QGraphicsItem *parent = nullptr);
  ~LayerGraphicsItem() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_GRAPHICS_ITEM_H
