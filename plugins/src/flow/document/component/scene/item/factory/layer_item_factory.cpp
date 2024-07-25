/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/item/factory/layer_item_factory.h"

#include "flow/document/component/scene/item/layer_item.h"
#include "flow/document/flow/group_layer.h"
#include "flow/document/flow/node_layer.h"
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ---------------------------- GroupLayerItemFactory ----------------------- */

GroupLayerItemFactory::GroupLayerItemFactory(QObject* parent)
    : ItemFactory(parent) {}

GroupLayerItemFactory::~GroupLayerItemFactory() = default;

QString GroupLayerItemFactory::getObjectClassName() const {
  return GroupLayer::sGetClassName();
}

ObjectItem* GroupLayerItemFactory::create(Object* object,
                                          FlowDocument* document,
                                          QGraphicsItem* parent) const {
  return new GroupLayerItem(static_cast<GroupLayer*>(object), document, parent);
}

/* ---------------------------- NodeLayerItemFactory ------------------------ */

NodeLayerItemFactory::NodeLayerItemFactory(QObject* parent)
    : ItemFactory(parent) {}

NodeLayerItemFactory::~NodeLayerItemFactory() = default;

QString NodeLayerItemFactory::getObjectClassName() const {
  return NodeLayer::sGetClassName();
}

ObjectItem* NodeLayerItemFactory::create(Object* object, FlowDocument* document,
                                         QGraphicsItem* parent) const {
  return new NodeLayerItem(static_cast<NodeLayer*>(object), document, parent);
}

}  // namespace flow