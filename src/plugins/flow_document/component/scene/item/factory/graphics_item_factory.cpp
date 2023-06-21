/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/factory/graphics_item_factory.h"

#include "flow_document/component/scene/item/layer_graphics_item.h"
#include "flow_document/component/scene/item/node_graphics_item.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/node.h"
#include "flow_document/flow/node_layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ---------------------------- GraphicsItemFactory ------------------------- */

GraphicsItemFactory::GraphicsItemFactory(QObject* parent) : QObject(parent) {}

GraphicsItemFactory::~GraphicsItemFactory() = default;

/* ---------------------------- GroupLayerItemFactory ----------------------- */

GroupLayerItemFactory::GroupLayerItemFactory(QObject* parent)
    : GraphicsItemFactory(parent) {}

GroupLayerItemFactory::~GroupLayerItemFactory() = default;

QString GroupLayerItemFactory::getObjectClass() const {
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

QString NodeLayerItemFactory::getObjectClass() const {
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

QString NodeItemFactory::getObjectClass() const {
  return Node::getStaticClassName();
}

GraphicsItem* NodeItemFactory::create(Object* object, FlowDocument* document,
                                      QGraphicsItem* parent) const {
  return new NodeGraphicsItem(static_cast<Node*>(object), document, parent);
}

}  // namespace flow_document