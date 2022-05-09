/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_item.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/object.h>
/* -------------------------------------------------------------------------- */

FlowItem::FlowItem(flow::Object *object, QGraphicsItem *parent)
    : QGraphicsObject(parent), m_object(object), m_hovered(false)
{
  setAcceptedMouseButtons(Qt::MouseButton{});
  setAcceptHoverEvents(true);
  setFlag(QGraphicsItem::ItemIsSelectable);
}

FlowItem::~FlowItem() = default;

flow::Object *FlowItem::getObject() const { return m_object; }

void FlowItem::setHovered(bool hovered)
{
  if (m_hovered == hovered) return;

  m_hovered = hovered;
  update();
}

bool FlowItem::isHovered() const { return m_hovered; }