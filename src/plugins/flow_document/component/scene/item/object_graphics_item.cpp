/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/object_graphics_item.h"

#include "flow_document/component/scene/item/factory/graphics_item_factory.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsScene>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

ObjectGraphicsItem::ObjectGraphicsItem(Object* object, FlowDocument* document,
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

  connect(m_document, &FlowDocument::event, this, &ObjectGraphicsItem::onEvent);
}

ObjectGraphicsItem::~ObjectGraphicsItem() = default;

void ObjectGraphicsItem::setHovered(bool hovered) {
  if (m_hovered == hovered) return;

  m_hovered = hovered;
  update();
}

bool ObjectGraphicsItem::isHovered() const { return m_hovered; }

Object* ObjectGraphicsItem::getObject() const { return m_object; }

FlowDocument* ObjectGraphicsItem::getDocument() const { return m_document; }

QRectF ObjectGraphicsItem::boundingRect() const { return QRectF{}; }

void ObjectGraphicsItem::paint(QPainter*, const QStyleOptionGraphicsItem*,
                               QWidget*) {}

void ObjectGraphicsItem::onEvent(const ChangeEvent& event) {}

}  // namespace flow_document