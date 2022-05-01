/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_node_painter.h"
#include "flow/plugins/document/flow/flow_node_item.h"
/* -------------------------------------------------------------------------- */

FlowNodePainter::FlowNodePainter(const FlowNodeItem &node_item)
    : m_node_item(node_item)
{}

FlowNodePainter::~FlowNodePainter() = default;

void FlowNodePainter::paint(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{
  paintNodeRect(painter, option);
  paintNodePins(painter, option);
  paintNodeLabel(painter, option);
  paintNodePinLabels(painter, option);
}

void FlowNodePainter::paintNodeRect(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{
  auto hovered = option->state & QStyle::State_MouseOver;
  auto selected = option->state & QStyle::State_Selected;
  auto rect = m_node_item.boundingRect();

  auto color = selected ? QColor(255, 165, 0) : QColor(255, 255, 255);
  auto pen_width = hovered ? 1.5 : 1.0;

  QLinearGradient gradient(rect.bottomLeft(), rect.topRight());

  gradient.setColorAt(0.0, QColor(160, 160, 164));
  gradient.setColorAt(0.03, QColor(80, 80, 80));
  gradient.setColorAt(0.97, QColor(64, 64, 64));
  gradient.setColorAt(1.0, QColor(58, 58, 58));

  painter->save();
  painter->setBrush(gradient);
  painter->setPen(QPen(color, pen_width));
  painter->drawRoundedRect(rect, 3.0, 3.0);
  painter->restore();
}

void FlowNodePainter::paintNodePins(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{}

void FlowNodePainter::paintNodeLabel(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{}

void FlowNodePainter::paintNodePinLabels(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{}
