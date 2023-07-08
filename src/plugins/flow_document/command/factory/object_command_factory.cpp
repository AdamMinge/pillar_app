/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/factory/object_command_factory.h"

#include "flow_document/flow/object.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------- ObjectCommandFactory ------------------------- */

ObjectCommandFactory::ObjectCommandFactory(QObject* parent) : QObject(parent) {}

ObjectCommandFactory::~ObjectCommandFactory() = default;

/* ----------------------------------- Utils -------------------------------- */

[[nodiscard]] ObjectCommandFactory* getObjectCommandFactoryByObject(
    Object* object) {
  if (object) {
    auto& manager = egnite::PluginManager::getInstance();
    auto inherited_classes = object->getInheritedClassNames();
    inherited_classes.prepend(object->getClassName());

    for (const auto& inherited_class : inherited_classes) {
      auto factory =
          manager.findIf<ObjectCommandFactory>([inherited_class](auto factory) {
            return factory->getObjectClassName() == inherited_class;
          });

      if (factory) return factory;
    }
  }

  return nullptr;
}

}  // namespace flow_document
