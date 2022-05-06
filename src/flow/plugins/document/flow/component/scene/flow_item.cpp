/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_item.h"
/* -------------------------------------------------------------------------- */

FlowItem::FlowItem(QGraphicsItem *parent)
    : QGraphicsObject(parent), m_hovered(false)
{
  setAcceptedMouseButtons(Qt::MouseButton{});
  setAcceptHoverEvents(true);
  setFlag(QGraphicsItem::ItemIsSelectable);
}

FlowItem::~FlowItem() = default;

void FlowItem::setHovered(bool hovered)
{
  if (m_hovered == hovered) return;

  m_hovered = hovered;
  update();
}

bool FlowItem::isHovered() const { return m_hovered; }