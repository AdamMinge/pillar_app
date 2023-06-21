#ifndef FLOW_DOCUMENT_FLOW_GRAPHICS_ITEM_H
#define FLOW_DOCUMENT_FLOW_GRAPHICS_ITEM_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/graphics_item.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Flow;
class LayerGraphicsItem;

class FLOW_DOCUMENT_API FlowGraphicsItem : public GraphicsItem {
  Q_OBJECT

 public:
  explicit FlowGraphicsItem(Flow* flow, FlowDocument* document,
                            QGraphicsItem* parent = nullptr);
  ~FlowGraphicsItem() override;

  [[nodiscard]] Flow* getFlow() const;

 private:
  LayerGraphicsItem* m_root_layer_item;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_GRAPHICS_ITEM_H
