/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_node_item.h"
#include "flow/plugins/document/flow/component/scene/flow_node_geometry.h"
#include "flow/plugins/document/flow/component/scene/flow_node_painter.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QPainter>
#include <QStyleOptionGraphicsItem>
/* ---------------------------------- LibFlow ------------------------------- */
#include "flow/libflow/node/node.h"
/* -------------------------------------------------------------------------- */


FlowNodeItem::FlowNodeItem(FlowDocument *document, flow::node::Node *node)
    : FlowItem(document, node),
      m_node_painter(std::make_unique<FlowNodePainter>(*this)),
      m_node_geometry(std::make_unique<FlowNodeGeometry>(*this))
{
  setPos(getNode()->getPosition());
}

FlowNodeItem::~FlowNodeItem() = default;

flow::node::Node *FlowNodeItem::getNode() const
{
  return dynamic_cast<flow::node::Node *>(getObject());
}

QRectF FlowNodeItem::boundingRect() const
{
  return m_node_geometry->getBoundingRect();
}

const FlowNodePainter *FlowNodeItem::getPainter() const
{
  return m_node_painter.get();
}

const FlowNodeGeometry *FlowNodeItem::getGeometry() const
{
  return m_node_geometry.get();
}

void FlowNodeItem::paint(
  QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setClipRect(option->exposedRect);
  m_node_painter->paint(painter, option);
}
