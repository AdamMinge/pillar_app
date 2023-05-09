/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/graphics_item.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

GraphicsItem::GraphicsItem(QGraphicsItem *parent)
    : QGraphicsObject(parent), m_hovered(false) {
  setAcceptedMouseButtons(Qt::MouseButton{});
  setAcceptHoverEvents(true);
  setFlag(QGraphicsItem::ItemIsSelectable);
}

GraphicsItem::~GraphicsItem() = default;

void GraphicsItem::setHovered(bool hovered) {
  if (m_hovered == hovered) return;

  m_hovered = hovered;
  update();
}

bool GraphicsItem::isHovered() const { return m_hovered; }

}  // namespace flow_document