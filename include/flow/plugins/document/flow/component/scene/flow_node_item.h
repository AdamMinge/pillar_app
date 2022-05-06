#ifndef PLUGIN_FLOW_FLOW_NODE_ITEM_H
#define PLUGIN_FLOW_FLOW_NODE_ITEM_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_item.h"
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FlowNodePainter;
class FlowNodeGeometry;

namespace flow::node
{
  class Node;
}

class FLOW_DOCUMENT_API FlowNodeItem : public FlowItem
{
  Q_OBJECT

public:
  explicit FlowNodeItem(const flow::node::Node &node);
  ~FlowNodeItem() override;

  [[nodiscard]] const flow::node::Node &getNode() const;
  [[nodiscard]] QRectF boundingRect() const override;

protected:
  void paint(
    QPainter *painter, const QStyleOptionGraphicsItem *option,
    QWidget *widget) override;

private:
  const flow::node::Node &m_node;
  std::unique_ptr<FlowNodePainter> m_node_painter;
  std::unique_ptr<FlowNodeGeometry> m_node_geometry;
};

#endif//PLUGIN_FLOW_FLOW_NODE_ITEM_H
