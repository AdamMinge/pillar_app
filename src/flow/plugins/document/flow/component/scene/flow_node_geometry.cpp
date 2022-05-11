/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_node_geometry.h"
#include "flow/plugins/document/flow/component/scene/flow_node_item.h"
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
  const auto style = FlowStyleManager::getInstance().getNodeStyles(m_node_item);
  const auto label_size = calculateLabelSize();
  const auto pins_size = calculatePinsSize();
  const auto widget_size = calculateWidgetSize();

  m_size.setWidth(
    std::max(pins_size.width() + widget_size.width(), label_size.width()) +
    style.margins.left() + style.margins.right());
  m_size.setHeight(
    label_size.height() + std::max(pins_size.height(), widget_size.height()) +
    style.margins.top() + style.margins.bottom());

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

QPointF FlowNodeGeometry::getWidgetPosition() const
{
  return m_widget_position;
}

QSizeF FlowNodeGeometry::calculateLabelSize() const
{
  const auto style = FlowStyleManager::getInstance().getNodeStyles(m_node_item);
  const auto font_metrics = QFontMetricsF(style.font);
  const auto label = m_node_item.getNode()->getName();
  const auto label_size =
    QSizeF{font_metrics.horizontalAdvance(label), font_metrics.height()};

  return label_size;
}

QSizeF FlowNodeGeometry::calculateWidgetSize() const { return QSizeF{}; }

QSizeF FlowNodeGeometry::calculatePinsSize() const
{
  const auto style = FlowStyleManager::getInstance().getNodeStyles(m_node_item);
  auto max_pins = std::max(
    m_node_item.getNode()->getPinsCounts(flow::node::Pin::Type::In),
    m_node_item.getNode()->getPinsCounts(flow::node::Pin::Type::Out));

  auto width = calculatePinsWidth(flow::node::Pin::Type::In) +
               calculatePinsWidth(flow::node::Pin::Type::Out);
  auto height = (style.pin.size.height() + style.pin.margins.top() +
                 style.pin.margins.left()) *
                max_pins;

  return {width, height};
}

float FlowNodeGeometry::calculatePinsWidth(flow::node::Pin::Type type) const
{
  const auto style = FlowStyleManager::getInstance().getNodeStyles(m_node_item);
  const auto font_metrics = QFontMetricsF(style.pin.font);

  auto width = style.pin.margins.left() + style.pin.margins.right();
  for (auto i = 0; i < m_node_item.getNode()->getPinsCounts(type); ++i)
  {
    auto name = m_node_item.getNode()->getPin(type, i).getCaption();
    width = std::max(width, font_metrics.horizontalAdvance(name));
  }

  return static_cast<float>(width);
}

QPointF FlowNodeGeometry::calculateLabelPosition() const
{
  const auto style = FlowStyleManager::getInstance().getNodeStyles(m_node_item);
  const auto rect = getBoundingRect();
  const auto font_metrics = QFontMetricsF(style.font);
  const auto label = m_node_item.getNode()->getName();
  const auto label_size =
    QSizeF{font_metrics.horizontalAdvance(label), font_metrics.height()};

  return QPointF{
    rect.center().x() - label_size.width() / 2,
    rect.top() + label_size.height() / 2 + style.margins.top()};
}

FlowNodeGeometry::PinToPos FlowNodeGeometry::calculatePinPositions() const
{
  const auto style = FlowStyleManager::getInstance().getNodeStyles(m_node_item);
  const auto node = m_node_item.getNode();
  const auto rect = getBoundingRect();
  const auto label_size = calculateLabelSize();

  auto pin_positions = PinToPos{};
  for (auto type : {flow::node::Pin::Type::In, flow::node::Pin::Type::Out})
  {
    auto pins_count = node->getPinsCounts(type);
    auto height_step = (rect.height() - label_size.height()) / (pins_count + 1);

    for (auto index = 0; index < node->getPinsCounts(type); ++index)
    {
      const auto x = type == flow::node::Pin::Type::In
                       ? rect.left() + style.pin.margins.left()
                       : rect.right() - style.pin.margins.right();
      const auto y =
        rect.top() + label_size.height() + (height_step * (index + 1));

      pin_positions.insert(std::make_pair(type, index), QPointF(x, y));
    }
  }

  return pin_positions;
}

QPointF FlowNodeGeometry::calculateWidgetPosition() const { return QPointF{}; }
