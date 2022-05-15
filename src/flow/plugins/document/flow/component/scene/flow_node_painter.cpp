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
  const auto &node_style = getNodeStyle(m_node_item);
  const auto rect = m_node_item.boundingRect();

  QLinearGradient linear_gradient(rect.bottomLeft(), rect.topRight());
  linear_gradient.setColorAt(
    node_style.findGradientScale()[0], node_style.findGradient()[0]);
  linear_gradient.setColorAt(
    node_style.findGradientScale()[0], node_style.findGradient()[1]);
  linear_gradient.setColorAt(
    node_style.findGradientScale()[0], node_style.findGradient()[2]);
  linear_gradient.setColorAt(
    node_style.findGradientScale()[0], node_style.findGradient()[3]);

  painter->save();
  painter->setBrush(linear_gradient);
  painter->setPen(
    QPen(node_style.findBorderColor(), node_style.findBorderSize()));
  painter->drawRoundedRect(
    rect, node_style.findBorderRadius(), node_style.findBorderRadius());
  painter->restore();
}

void FlowNodePainter::paintNodeLabel(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{
  const auto &node_style = getNodeStyle(m_node_item);
  const auto node = m_node_item.getNode();
  const auto geometry = m_node_item.getGeometry();

  const auto label = node->getName();
  const auto label_pos = geometry->getLabelPosition();

  painter->save();
  painter->setFont(node_style.findFont());
  painter->setPen(node_style.findFontColor());
  painter->drawText(label_pos, label);
  painter->restore();
}

void FlowNodePainter::paintNodePins(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{
  const auto &pin_style = getPinStyle(m_node_item);
  const auto node = m_node_item.getNode();
  const auto geometry = m_node_item.getGeometry();

  for (auto type : {flow::node::Pin::Type::In, flow::node::Pin::Type::Out})
  {
    for (auto index = 0; index < node->getPinsCounts(type); ++index)
    {
      const auto pin_pos = geometry->getPinPosition(type, index);

      painter->save();
      painter->setBrush(pin_style.findColor());
      painter->setPen(pin_style.findBorderColor());
      painter->drawEllipse(
        pin_pos, pin_style.findSize().width(), pin_style.findSize().height());
      painter->restore();
    }
  }
}

void FlowNodePainter::paintNodePinLabels(
  QPainter *painter, const QStyleOptionGraphicsItem *option)
{
  const auto &pin_style = getPinStyle(m_node_item);
  const auto node = m_node_item.getNode();
  const auto geometry = m_node_item.getGeometry();

  for (auto type : {flow::node::Pin::Type::In, flow::node::Pin::Type::Out})
  {
    for (auto index = 0; index < node->getPinsCounts(type); ++index)
    {
      const auto pin_label_pos = geometry->getPinLabelPosition(type, index);
      const auto pin_label = node->getPin(type, index).getCaption();

      painter->save();
      painter->setFont(pin_style.findFont());
      painter->setPen(pin_style.findFontColor());
      painter->drawText(pin_label_pos, pin_label);
      painter->restore();
    }
  }
}
