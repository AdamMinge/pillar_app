/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/object_item.h"

#include "flow_document/component/scene/item/factory/item_factory.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsScene>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

ObjectItem::ObjectItem(Object* object, FlowDocument* document,
                       QGraphicsItem* parent)
    : QGraphicsObject(parent), m_object(object), m_document(document) {
  connect(m_document, &FlowDocument::event, this, &ObjectItem::onEvent);
}

ObjectItem::~ObjectItem() = default;

void ObjectItem::init() {}

Object* ObjectItem::getObject() const { return m_object; }

FlowDocument* ObjectItem::getDocument() const { return m_document; }

QRectF ObjectItem::boundingRect() const { return QRectF{}; }

void ObjectItem::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) {}

QVariant ObjectItem::itemChange(QGraphicsItem::GraphicsItemChange change,
                                const QVariant& value) {
  if (change == QGraphicsItem::ItemSceneHasChanged) {
    onSceneChanged();
  }

  return QGraphicsObject::itemChange(change, value);
}

void ObjectItem::onEvent(const ChangeEvent& event) {}

void ObjectItem::onSceneChanged() {}

}  // namespace flow_document