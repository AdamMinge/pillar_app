#ifndef PLUGIN_FLOW_FLOW_NODE_ITEM_H
#define PLUGIN_FLOW_FLOW_NODE_ITEM_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/flow_item.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Node;

class FlowNodePainter;
class FlowNodeGeometry;

class FLOW_DOCUMENT_API FlowNodeItem : public FlowItem {
  Q_OBJECT

 public:
  explicit FlowNodeItem(FlowDocument *document, Node *node);
  ~FlowNodeItem() override;

  [[nodiscard]] Node *getNode() const;
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

#endif  // PLUGIN_FLOW_FLOW_NODE_ITEM_H
