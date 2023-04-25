/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/flow_graphics_item.h"

#include "flow_document/event/objects_event.h"
#include "flow_document/flow/flow_object.h"
#include "flow_document/flow_document.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowGraphicsItem::FlowGraphicsItem(FlowDocument *document, FlowObject *object,
                                   QGraphicsItem *parent)
    : QGraphicsObject(parent),
      m_document(document),
      m_object(object),
      m_hovered(false) {
  setAcceptedMouseButtons(Qt::MouseButton{});
  setAcceptHoverEvents(true);
  setFlag(QGraphicsItem::ItemIsSelectable);
  setPos(m_object->getPosition());

  connect(document, qOverload<const ChangeEvent &>(&FlowDocument::event), this,
          qOverload<const ChangeEvent &>(&FlowGraphicsItem::onEvent));
}

FlowGraphicsItem::~FlowGraphicsItem() = default;

FlowObject *FlowGraphicsItem::getObject() const { return m_object; }

FlowDocument *FlowGraphicsItem::getDocument() const { return m_document; }

void FlowGraphicsItem::setHovered(bool hovered) {
  if (m_hovered == hovered) return;

  m_hovered = hovered;
  update();
}

bool FlowGraphicsItem::isHovered() const { return m_hovered; }

void FlowGraphicsItem::onEvent(const ChangeEvent &event) {
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