#ifndef FLOW_DOCUMENT_FLOW_NODE_ITEM_H
#define FLOW_DOCUMENT_FLOW_NODE_ITEM_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/flow_graphics_item.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowNode;

class FlowNodePainter;
class FlowNodeGeometry;

class FLOW_DOCUMENT_API FlowNodeGraphicsItem : public FlowGraphicsItem {
  Q_OBJECT

 public:
  explicit FlowNodeGraphicsItem(FlowDocument *document, FlowNode *node);
  ~FlowNodeGraphicsItem() override;

  [[nodiscard]] FlowNode *getNode() const;
  [[nodiscard]] QRectF boundingRect() const override;

  [[nodiscard]] const FlowNodePainter *getPainter() const;
  [[nodiscard]] const FlowNodeGeometry *getGeometry() const;

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

 private:
  std::unique_ptr<FlowNodePainter> m_node_painter;
  std::unique_ptr<FlowNodeGeometry> m_node_geometry;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_NODE_ITEM_H
