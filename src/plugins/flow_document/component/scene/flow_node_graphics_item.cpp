/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/flow_node_graphics_item.h"

#include "flow_document/component/scene/flow_node_geometry.h"
#include "flow_document/component/scene/flow_node_painter.h"
#include "flow_document/flow/flow_node.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QPainter>
#include <QStyleOptionGraphicsItem>
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowNodeGraphicsItem::FlowNodeGraphicsItem(FlowDocument *document,
                                           FlowNode *node)
    : FlowGraphicsItem(document, node),
      m_node_painter(std::make_unique<FlowNodePainter>(*this)),
      m_node_geometry(std::make_unique<FlowNodeGeometry>(*this)) {}

FlowNodeGraphicsItem::~FlowNodeGraphicsItem() = default;

FlowNode *FlowNodeGraphicsItem::getNode() const {
  return dynamic_cast<FlowNode *>(getObject());
}

QRectF FlowNodeGraphicsItem::boundingRect() const {
  return m_node_geometry->getBoundingRect();
}

const FlowNodePainter *FlowNodeGraphicsItem::getPainter() const {
  return m_node_painter.get();
}

const FlowNodeGeometry *FlowNodeGraphicsItem::getGeometry() const {
  return m_node_geometry.get();
}

void FlowNodeGraphicsItem::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem *option,
                                 QWidget *widget) {
  painter->setClipRect(option->exposedRect);
  m_node_painter->paint(painter, option);
}

}  // namespace flow_document