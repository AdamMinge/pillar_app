/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_node_painter.h"
#include "flow/plugins/document/flow/component/scene/flow_node_geometry.h"
#include "flow/plugins/document/flow/component/scene/flow_node_item.h"
#include "flow/plugins/document/flow/component/scene/flow_style_manager.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/node.h>
/* -------------------------------------------------------------------------- */

FlowNodePainter::FlowNodePainter(const FlowNodeItem &node_item)
    : m_node_item(node_item)
{}

FlowNodePainter::~FlowNodePainter() = default;

void FlowNodePainter::paint(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{
  paintNodeRect(painter, option);
  paintNodeLabel(painter, option);
  paintNodePins(painter, option);
  paintNodePinLabels(painter, option);
}

void FlowNodePainter::paintNodeRect(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{
  const auto rect = m_node_item.boundingRect();
  const auto &style =
    FlowStyleManager::getInstance().getNodeStyles(m_node_item);

  QLinearGradient gradient(rect.bottomLeft(), rect.topRight());
  gradient.setColorAt(style.gradient_scale[0], style.gradient[0]);
  gradient.setColorAt(style.gradient_scale[0], style.gradient[1]);
  gradient.setColorAt(style.gradient_scale[0], style.gradient[2]);
  gradient.setColorAt(style.gradient_scale[0], style.gradient[3]);

  painter->save();
  painter->setBrush(gradient);
  painter->setPen(QPen(style.border_color, style.border_size));
  painter->drawRoundedRect(rect, style.border_radius, style.border_radius);
  painter->restore();
}

void FlowNodePainter::paintNodeLabel(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{
  const auto node = m_node_item.getNode();
  const auto geometry = m_node_item.getGeometry();
  const auto &style =
    FlowStyleManager::getInstance().getNodeStyles(m_node_item);

  const auto label = node->getName();
  const auto label_pos = geometry->getLabelPosition();

  painter->save();
  painter->setFont(style.font);
  painter->drawText(label_pos, label);
  painter->restore();
}

void FlowNodePainter::paintNodePins(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{
  const auto node = m_node_item.getNode();
  const auto geometry = m_node_item.getGeometry();
  const auto &style =
    FlowStyleManager::getInstance().getNodeStyles(m_node_item);

  for (auto type : {flow::node::Pin::Type::In, flow::node::Pin::Type::Out})
  {
    for (auto index = 0; index < node->getPinsCounts(type); ++index)
    {
      const auto pin_pos = geometry->getPinPosition(type, index);

      painter->save();
      painter->setBrush(style.pin.color);
      painter->setPen(style.pin.border_color);
      painter->drawEllipse(
        pin_pos, style.pin.size.width(), style.pin.size.height());
      painter->restore();
    }
  }
}

void FlowNodePainter::paintNodePinLabels(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{}
