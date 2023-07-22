/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/factory/item_factory.h"

#include "flow_document/component/scene/item/connection_item.h"
#include "flow_document/component/scene/item/flow_item.h"
#include "flow_document/component/scene/item/layer_item.h"
#include "flow_document/component/scene/item/node_item.h"
#include "flow_document/flow/connection.h"
#include "flow_document/flow/connection_layer.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/node.h"
#include "flow_document/flow/node_layer.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------------- ItemFactory ----------------------------- */

ItemFactory::ItemFactory(QObject* parent) : QObject(parent) {}

ItemFactory::~ItemFactory() = default;

/* ------------------------------- FlowItemFactory -------------------------- */

FlowItemFactory::FlowItemFactory(QObject* parent) : ItemFactory(parent) {}

FlowItemFactory::~FlowItemFactory() = default;

QString FlowItemFactory::getObjectClassName() const {
  return Flow::sGetClassName();
}

ObjectItem* FlowItemFactory::create(Object* object, FlowDocument* document,
                                    QGraphicsItem* parent) const {
  return new FlowItem(static_cast<Flow*>(object), document, parent);
}

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

/* ------------------------- ConnectionLayerItemFactory --------------------- */

ConnectionLayerItemFactory::ConnectionLayerItemFactory(QObject* parent)
    : ItemFactory(parent) {}

ConnectionLayerItemFactory::~ConnectionLayerItemFactory() = default;

QString ConnectionLayerItemFactory::getObjectClassName() const {
  return ConnectionLayer::sGetClassName();
}

ObjectItem* ConnectionLayerItemFactory::create(Object* object,
                                               FlowDocument* document,
                                               QGraphicsItem* parent) const {
  return new ConnectionLayerItem(static_cast<ConnectionLayer*>(object),
                                 document, parent);
}

/* ------------------------------- NodeItemFactory -------------------------- */

NodeItemFactory::NodeItemFactory(QObject* parent) : ItemFactory(parent) {}

NodeItemFactory::~NodeItemFactory() = default;

QString NodeItemFactory::getObjectClassName() const {
  return Node::sGetClassName();
}

ObjectItem* NodeItemFactory::create(Object* object, FlowDocument* document,
                                    QGraphicsItem* parent) const {
  return new NodeItem(static_cast<Node*>(object), document, parent);
}

/* ---------------------------- ConnectionItemFactory ----------------------- */

ConnectionItemFactory::ConnectionItemFactory(QObject* parent)
    : ItemFactory(parent) {}

ConnectionItemFactory::~ConnectionItemFactory() = default;

QString ConnectionItemFactory::getObjectClassName() const {
  return Connection::sGetClassName();
}

ObjectItem* ConnectionItemFactory::create(Object* object,
                                          FlowDocument* document,
                                          QGraphicsItem* parent) const {
  return new ConnectionItem(static_cast<Connection*>(object), document, parent);
}

/* ----------------------------------- Utils -------------------------------- */

ObjectItem* createItem(Object* object, FlowDocument* document,
                       QGraphicsItem* parent) {
  auto factory = getItemFactoryByObject(object);
  if (!factory) return nullptr;

  return factory->create(object, document, parent);
}

ItemFactory* getItemFactoryByObject(Object* object) {
  if (object) {
    auto& manager = egnite::PluginManager::getInstance();
    auto inherited_classes = object->getInheritedClassNames();
    inherited_classes.prepend(object->getClassName());

    for (const auto& inherited_class : inherited_classes) {
      auto factory =
          manager.findIf<ItemFactory>([inherited_class](auto factory) {
            return factory->getObjectClassName() == inherited_class;
          });

      if (factory) return factory;
    }
  }

  return nullptr;
}

}  // namespace flow_document