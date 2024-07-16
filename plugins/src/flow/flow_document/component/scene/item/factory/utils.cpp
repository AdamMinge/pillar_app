/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/item/factory/utils.h"

#include "flow_document/component/scene/item/object_item.h"
#include "flow_document/flow/object.h"
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------------- Qtils -------------------------------- */

ObjectItem* createItem(Object* object, FlowDocument* document,
                       QGraphicsItem* parent) {
  auto factory = getItemFactoryByObject(object);
  if (!factory) return nullptr;

  auto object_item = factory->create(object, document, parent);
  object_item->init();

  return object_item;
}

ItemFactory* getItemFactoryByObject(Object* object) {
  if (object) {
    auto& manager = pillar::PluginManager::getInstance();
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