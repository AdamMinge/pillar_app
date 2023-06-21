/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/graphics_item.h"

#include "flow_document/component/scene/item/factory/graphics_item_factory.h"
#include "flow_document/flow_document.h"
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
  setFlag(QGraphicsItem::ItemIsSelectable);

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

QRectF GraphicsItem::boundingRect() const { return QRectF(); }

void GraphicsItem::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) {
}

void GraphicsItem::onEvent(const ChangeEvent& event) {}

GraphicsItem* GraphicsItem::creatItem(Object* object, FlowDocument* document) {
  auto factory = getFactoryByObject(object);
  Q_ASSERT(factory);

  return factory->create(object, document, this);
}

GraphicsItemFactory* GraphicsItem::getFactoryByObject(Object* object) const {
  if (object) {
    auto& manager = egnite::PluginManager::getInstance();
    auto factories = manager.getObjects<GraphicsItemFactory>();

    auto inherited_classes = object->getInheritedClasses();
    inherited_classes.prepend(object->getClassName());

    for (const auto& inherited_class : inherited_classes) {
      auto found_factory =
          std::find_if(factories.cbegin(), factories.cend(),
                       [&inherited_class](const auto& factory) {
                         return factory->getObjectClass() == inherited_class;
                       });

      if (found_factory != factories.cend()) return *found_factory;
    }
  }

  return nullptr;
}

}  // namespace flow_document