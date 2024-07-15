/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/factory/utils.h"

#include "flow_document/component/properties/object_properties.h"
#include "flow_document/flow/object.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ----------------------------------- Qtils -------------------------------- */

ObjectProperties* createObjectProperties(Object* object, QObject* parent) {
  auto factory = getObjectPropertiesFactoryObject(object);
  if (!factory) return nullptr;

  auto object_properties = factory->create(parent);
  object_properties->init();

  return object_properties;
}

ObjectPropertiesFactory* getObjectPropertiesFactoryObject(Object* object) {
  if (object) {
    auto& manager = egnite::PluginManager::getInstance();
    auto inherited_classes = object->getInheritedClassNames();
    inherited_classes.prepend(object->getClassName());

    for (const auto& inherited_class : inherited_classes) {
      auto factory = manager.findIf<ObjectPropertiesFactory>(
          [inherited_class](auto factory) {
            return factory->getObjectClassName() == inherited_class;
          });

      if (factory) return factory;
    }
  }

  return nullptr;
}

}  // namespace flow_document