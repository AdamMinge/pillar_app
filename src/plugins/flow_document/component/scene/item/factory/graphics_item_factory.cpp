/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/factory/graphics_item_factory.h"

#include "flow_document/component/scene/item/flow_graphics_item.h"
#include "flow_document/component/scene/item/layer_graphics_item.h"
#include "flow_document/component/scene/item/node_graphics_item.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/node.h"
#include "flow_document/flow/node_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ---------------------------- GraphicsItemFactory ------------------------- */

GraphicsItemFactory::GraphicsItemFactory(QObject* parent) : QObject(parent) {}

GraphicsItemFactory::~GraphicsItemFactory() = default;

/* ------------------------------- FlowItemFactory -------------------------- */

FlowItemFactory::FlowItemFactory(QObject* parent)
    : GraphicsItemFactory(parent) {}

FlowItemFactory::~FlowItemFactory() = default;

QString FlowItemFactory::getObjectClassName() const {
  return Flow::getStaticClassName();
}

GraphicsItem* FlowItemFactory::create(Object* object, FlowDocument* document,
                                      QGraphicsItem* parent) const {
  return new FlowGraphicsItem(static_cast<Flow*>(object), document, parent);
}

/* ---------------------------- GroupLayerItemFactory ----------------------- */

GroupLayerItemFactory::GroupLayerItemFactory(QObject* parent)
    : GraphicsItemFactory(parent) {}

GroupLayerItemFactory::~GroupLayerItemFactory() = default;

QString GroupLayerItemFactory::getObjectClassName() const {
  return GroupLayer::getStaticClassName();
}

GraphicsItem* GroupLayerItemFactory::create(Object* object,
                                            FlowDocument* document,
                                            QGraphicsItem* parent) const {
  return new GroupLayerGraphicsItem(static_cast<GroupLayer*>(object), document,
                                    parent);
}

/* ---------------------------- NodeLayerItemFactory ------------------------ */

NodeLayerItemFactory::NodeLayerItemFactory(QObject* parent)
    : GraphicsItemFactory(parent) {}

NodeLayerItemFactory::~NodeLayerItemFactory() = default;

QString NodeLayerItemFactory::getObjectClassName() const {
  return NodeLayer::getStaticClassName();
}

GraphicsItem* NodeLayerItemFactory::create(Object* object,
                                           FlowDocument* document,
                                           QGraphicsItem* parent) const {
  return new NodeLayerGraphicsItem(static_cast<NodeLayer*>(object), document,
                                   parent);
}

/* ------------------------------- NodeItemFactory -------------------------- */

NodeItemFactory::NodeItemFactory(QObject* parent)
    : GraphicsItemFactory(parent) {}

NodeItemFactory::~NodeItemFactory() = default;

QString NodeItemFactory::getObjectClassName() const {
  return Node::getStaticClassName();
}

GraphicsItem* NodeItemFactory::create(Object* object, FlowDocument* document,
                                      QGraphicsItem* parent) const {
  return new NodeGraphicsItem(static_cast<Node*>(object), document, parent);
}

/* ----------------------------------- Utils -------------------------------- */

GraphicsItem* createGraphicsItem(Object* object, FlowDocument* document,
                                 QGraphicsItem* parent) {
  auto factory = getGraphicsItemFactoryByObject(object);
  if (!factory) return nullptr;

  return factory->create(object, document, parent);
}

GraphicsItemFactory* getGraphicsItemFactoryByObject(Object* object) {
  if (object) {
    auto& manager = egnite::PluginManager::getInstance();
    auto inherited_classes = object->getInheritedClassNames();
    inherited_classes.prepend(object->getClassName());

    for (const auto& inherited_class : inherited_classes) {
      auto factory =
          manager.findIf<GraphicsItemFactory>([inherited_class](auto factory) {
            return factory->getObjectClassName() == inherited_class;
          });

      if (factory) return factory;
    }
  }

  return nullptr;
}

}  // namespace flow_document