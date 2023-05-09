/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/object_graphics_item.h"

#include "flow_document/flow/object.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

ObjectGraphicsItem::ObjectGraphicsItem(FlowDocument *document, Object *object,
                                       QGraphicsItem *parent)
    : GraphicsItem(parent), m_document(document), m_object(object) {
  setPos(m_object->getPosition());

  connect(m_document, qOverload<const ChangeEvent &>(&FlowDocument::event),
          this, qOverload<const ChangeEvent &>(&ObjectGraphicsItem::onEvent));
}

ObjectGraphicsItem::~ObjectGraphicsItem() = default;

Object *ObjectGraphicsItem::getObject() const { return m_object; }

FlowDocument *ObjectGraphicsItem::getDocument() const { return m_document; }

void ObjectGraphicsItem::onEvent(const ChangeEvent &event) {
  // TODO
}

}  // namespace flow_document