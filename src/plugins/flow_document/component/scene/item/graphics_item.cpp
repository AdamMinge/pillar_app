/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/graphics_item.h"

#include "flow_document/component/scene/item/factory/graphics_item_factory.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsScene>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

GraphicsItem::GraphicsItem(Object* object, FlowDocument* document,
                           QGraphicsItem* parent)
    : QGraphicsObject(parent),
      m_object(object),
      m_document(document),
      m_hovered(false) {
  setAcceptedMouseButtons(Qt::MouseButton{});
  setAcceptHoverEvents(true);
  setAcceptDrops(true);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setPos(m_object->getPosition());
  setVisible(m_object->isVisible());

  connect(m_document, &FlowDocument::event, this, &GraphicsItem::onEvent);
}

GraphicsItem::~GraphicsItem() = default;

void GraphicsItem::setHovered(bool hovered) {
  if (m_hovered == hovered) return;

  m_hovered = hovered;
  update();
}

bool GraphicsItem::isHovered() const { return m_hovered; }

Object* GraphicsItem::getObject() const { return m_object; }

FlowDocument* GraphicsItem::getDocument() const { return m_document; }

QRectF GraphicsItem::boundingRect() const { return QRectF{}; }

void GraphicsItem::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) {

}

void GraphicsItem::onEvent(const ChangeEvent& event) {}

}  // namespace flow_document