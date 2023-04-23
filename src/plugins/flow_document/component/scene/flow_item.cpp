/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/flow_item.h"

#include "flow_document/event/objects_event.h"
#include "flow_document/flow_document.h"
#include "flow_document/node/object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowItem::FlowItem(FlowDocument *document, Object *object,
                   QGraphicsItem *parent)
    : QGraphicsObject(parent),
      m_document(document),
      m_object(object),
      m_hovered(false) {
  setAcceptedMouseButtons(Qt::MouseButton{});
  setAcceptHoverEvents(true);
  setFlag(QGraphicsItem::ItemIsSelectable);

  connect(document, qOverload<const ChangeEvent &>(&FlowDocument::event), this,
          qOverload<const ChangeEvent &>(&FlowItem::onEvent));
}

FlowItem::~FlowItem() = default;

Object *FlowItem::getObject() const { return m_object; }

FlowDocument *FlowItem::getDocument() const { return m_document; }

void FlowItem::setHovered(bool hovered) {
  if (m_hovered == hovered) return;

  m_hovered = hovered;
  update();
}

bool FlowItem::isHovered() const { return m_hovered; }

void FlowItem::onEvent(const ChangeEvent &event) {
  switch (event.getType()) {
    case ChangeEvent::Type::ObjectsChangedProperties: {
      const auto &change_properties_event =
          static_cast<const ObjectsChangedPropertiesEvent &>(event);

      if (change_properties_event.contains(getObject()) &&
          change_properties_event.getProperties().testFlag(
              ObjectsChangedPropertiesEvent::Property::PositionProperty)) {
        setPos(getObject()->getPosition());
      }

      break;
    }
  }
}

}  // namespace flow_document