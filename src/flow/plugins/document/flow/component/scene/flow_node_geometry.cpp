/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_node_geometry.h"
#include "flow/plugins/document/flow/component/scene/flow_node_item.h"
#include "flow/plugins/document/flow/component/scene/flow_style.h"
#include "flow/plugins/document/flow/component/scene/flow_style_manager.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include "flow/libflow/node/node.h"
/* -------------------------------------------------------------------------- */

FlowNodeGeometry::FlowNodeGeometry(const FlowNodeItem &node_item)
    : m_node_item(node_item)
{
  recalculate();
}

FlowNodeGeometry::~FlowNodeGeometry() = default;

void FlowNodeGeometry::recalculate()
{
  const auto &node_style = getNodeStyle(m_node_item);
  const auto label_size = calculateLabelSize();
  const auto pins_size = calculatePinsSize();
  const auto widget_size = calculateWidgetSize();

  m_size.setWidth(
    std::max(pins_size.width() + widget_size.width(), label_size.width()) +
    node_style.getMargins().left() + node_style.getMargins().right());
  m_size.setHeight(
    label_size.height() + std::max(pins_size.height(), widget_size.height()) +
    node_style.getMargins().top() + node_style.getMargins().bottom());

  m_label_position = calculateLabelPosition();
  m_pin_positions = calculatePinPositions();
  m_widget_position = calculateWidgetPosition();
}

QRectF FlowNodeGeometry::getBoundingRect() const
{
  return QRectF{QPointF(-m_size.width() / 2.0, -m_size.height() / 2.0), m_size};
}

QPointF FlowNodeGeometry::getLabelPosition() const { return m_label_position; }

QPointF
FlowNodeGeometry::getPinPosition(flow::node::Pin::Type type, int index) const
{
  return m_pin_positions.value(std::make_pair(type, index), QPointF{});
}

QPointF FlowNodeGeometry::getPinLabelPosition(
  flow::node::Pin::Type type, int index) const
{
  const auto &pin_style = getPinStyle(m_node_item);
  const auto font_metrics = QFontMetricsF(pin_style.getFont());
  const auto label = m_node_item.getNode()->getPin(type, index).getCaption();

  auto pin_pos = getPinPosition(type, index);
  pin_pos.ry() -= pin_style.getSize().height() + font_metrics.height() / 3.0;
  pin_pos.rx() -= font_metrics.horizontalAdvance(label) / 2.0;

  return pin_pos;
}

QPointF FlowNodeGeometry::getWidgetPosition() const
{
  return m_widget_position;
}

QSizeF FlowNodeGeometry::calculateLabelSize() const
{
  const auto &node_style = getNodeStyle(m_node_item);
  const auto font_metrics = QFontMetricsF(node_style.getFont());
  const auto label = m_node_item.getNode()->getName();
  const auto label_size =
    QSizeF{font_metrics.horizontalAdvance(label), font_metrics.height()};

  return label_size;
}

QSizeF FlowNodeGeometry::calculateWidgetSize() const { return QSizeF{}; }

QSizeF FlowNodeGeometry::calculatePinsSize() const
{
  const auto &pin_style = getPinStyle(m_node_item);
  const auto font_metrics = QFontMetricsF(pin_style.getFont());

  auto max_pins = std::max(
    m_node_item.getNode()->getPinsCounts(flow::node::Pin::Type::In),
    m_node_item.getNode()->getPinsCounts(flow::node::Pin::Type::Out));

  auto width = calculatePinsWidth(flow::node::Pin::Type::In) +
               calculatePinsWidth(flow::node::Pin::Type::Out);
  auto height = (pin_style.getSize().height() + pin_style.getMargins().top() +
                 pin_style.getMargins().left() + font_metrics.height()) *
                max_pins;

  return {width, height};
}

float FlowNodeGeometry::calculatePinsWidth(flow::node::Pin::Type type) const
{
  const auto &pin_style = getPinStyle(m_node_item);
  const auto font_metrics = QFontMetricsF(pin_style.getFont());

  auto width = pin_style.getMargins().left() + pin_style.getMargins().right();
  for (auto i = 0; i < m_node_item.getNode()->getPinsCounts(type); ++i)
  {
    const auto name = m_node_item.getNode()->getPin(type, i).getCaption();
    width = std::max(width, font_metrics.horizontalAdvance(name));
  }

  return static_cast<float>(width);
}

QPointF FlowNodeGeometry::calculateLabelPosition() const
{
  const auto &node_style = getNodeStyle(m_node_item);
  const auto rect = getBoundingRect();
  const auto font_metrics = QFontMetricsF(node_style.getFont());
  const auto label = m_node_item.getNode()->getName();
  const auto label_size =
    QSizeF{font_metrics.horizontalAdvance(label), font_metrics.height()};

  return QPointF{
    rect.center().x() - label_size.width() / 2,
    rect.top() + label_size.height() / 2 + node_style.getMargins().top()};
}

FlowNodeGeometry::PinToPos FlowNodeGeometry::calculatePinPositions() const
{
  const auto &node_style = getNodeStyle(m_node_item);
  const auto &pin_style = getPinStyle(m_node_item);
  const auto node = m_node_item.getNode();
  const auto rect = getBoundingRect();
  const auto label_size = calculateLabelSize();
  const auto label_pos = calculateLabelPosition();

  auto pin_positions = PinToPos{};
  for (auto type : {flow::node::Pin::Type::In, flow::node::Pin::Type::Out})
  {
    auto pins_count = node->getPinsCounts(type);
    auto height_step =
      (rect.height() - (label_size.height() + node_style.getMargins().top())) /
      (pins_count + 1);

    for (auto index = 0; index < node->getPinsCounts(type); ++index)
    {
      const auto x = type == flow::node::Pin::Type::In
                       ? rect.left() + pin_style.getMargins().left()
                       : rect.right() - pin_style.getMargins().right();
      const auto y =
        label_pos.y() + label_size.height() / 2 + (height_step * (index + 1));

      pin_positions.insert(std::make_pair(type, index), QPointF(x, y));
    }
  }

  return pin_positions;
}

QPointF FlowNodeGeometry::calculateWidgetPosition() const { return QPointF{}; }
