/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_item.h"
#include "flow/plugins/document/flow/event/objects_event.h"
#include "flow/plugins/document/flow/flow_document.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/object.h>
/* -------------------------------------------------------------------------- */

FlowItem::FlowItem(
  FlowDocument *document, flow::Object *object, QGraphicsItem *parent)
    : QGraphicsObject(parent), m_document(document), m_object(object),
      m_hovered(false)
{
  setAcceptedMouseButtons(Qt::MouseButton{});
  setAcceptHoverEvents(true);
  setFlag(QGraphicsItem::ItemIsSelectable);

  connect(
    document,
    qOverload<const ObjectsChangedPropertiesEvent &>(&FlowDocument::event),
    this, qOverload<const ObjectsChangedPropertiesEvent &>(&FlowItem::onEvent));
}

FlowItem::~FlowItem() = default;

flow::Object *FlowItem::getObject() const { return m_object; }

FlowDocument *FlowItem::getDocument() const { return m_document; }

void FlowItem::setHovered(bool hovered)
{
  if (m_hovered == hovered) return;

  m_hovered = hovered;
  update();
}

bool FlowItem::isHovered() const { return m_hovered; }

void FlowItem::onEvent(const ObjectsChangedPropertiesEvent &event)
{
  if (
    event.contains(getObject()) &&
    event.getProperties().testFlag(
      ObjectsChangedPropertiesEvent::Property::PositionProperty))
  {
    setPos(getObject()->getPosition());
  }
}