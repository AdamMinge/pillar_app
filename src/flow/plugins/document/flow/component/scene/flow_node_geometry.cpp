/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_node_geometry.h"
#include "flow/plugins/document/flow/component/scene/flow_node_item.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include "flow/libflow/node/node.h"
/* -------------------------------------------------------------------------- */

FlowNodeGeometry::FlowNodeGeometry(const FlowNodeItem &node_item)
    : m_node_item(node_item), m_size(0, 0), m_spacing(20, 20)
{
  recalculate();
}

FlowNodeGeometry::~FlowNodeGeometry() = default;

void FlowNodeGeometry::recalculate()
{
  m_size = getPinsSize() + getWidgetSize() + getLabelSize();
}

QRectF FlowNodeGeometry::getBoundingRect() const
{
  return QRectF{QPointF(-m_size.width() / 2.0, -m_size.height() / 2.0), m_size};
}

QPointF
FlowNodeGeometry::getPinPosition(flow::node::Pin::Type type, int index) const
{
  return QPointF{};
}

QPointF FlowNodeGeometry::getWidgetPosition() const { return QPointF{}; }

QSizeF FlowNodeGeometry::getLabelSize() const { return QSizeF{}; }

QSizeF FlowNodeGeometry::getWidgetSize() const { return QSizeF{}; }

QSizeF FlowNodeGeometry::getPinsSize() const
{
  auto max_pins = std::max(
    m_node_item.getNode()->getPinsCounts(flow::node::Pin::Type::In),
    m_node_item.getNode()->getPinsCounts(flow::node::Pin::Type::Out));

  auto width = getPinsWidth(flow::node::Pin::Type::In) +
               getPinsWidth(flow::node::Pin::Type::Out) + 2 * m_spacing.width();
  auto height = max_pins * m_spacing.height();

  return {width, height};
}

float FlowNodeGeometry::getPinsWidth(flow::node::Pin::Type type) const
{
  auto width = 0.0;
  const auto font_metrics = QFontMetricsF(QFont{});

  for (auto i = 0; i < m_node_item.getNode()->getPinsCounts(type); ++i)
  {
    auto name = m_node_item.getNode()->getPin(type, i).getCaption();
    width = std::max(width, font_metrics.horizontalAdvance(name));
  }

  return static_cast<float>(width);
}
