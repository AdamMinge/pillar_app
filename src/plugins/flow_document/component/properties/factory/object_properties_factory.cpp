/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/factory/object_properties_factory.h"

#include "flow_document/component/properties/object_properties.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/node.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------- ObjectPropertiesFactory ----------------------- */

ObjectPropertiesFactory::ObjectPropertiesFactory(QObject* parent)
    : QObject(parent) {}

ObjectPropertiesFactory::~ObjectPropertiesFactory() = default;

/* --------------------------- LayerPropertiesFactory ----------------------- */

LayerPropertiesFactory::LayerPropertiesFactory(QObject* parent)
    : ObjectPropertiesFactory(parent) {}

ObjectProperties* LayerPropertiesFactory::create(QObject* parent) const {
  return new LayerProperties(parent);
}

QString LayerPropertiesFactory::getObjectClassName() const {
  return Layer::sGetClassName();
}

/* --------------------------- NodePropertiesFactory ------------------------ */

NodePropertiesFactory::NodePropertiesFactory(QObject* parent)
    : ObjectPropertiesFactory(parent) {}

ObjectProperties* NodePropertiesFactory::create(QObject* parent) const {
  return new NodeProperties(parent);
}

QString NodePropertiesFactory::getObjectClassName() const {
  return Node::sGetClassName();
}

/* ----------------------------------- Utils -------------------------------- */

ObjectProperties* createObjectProperties(Object* object, QObject* parent) {
  auto factory = getObjectPropertiesFactoryObject(object);
  if (!factory) return nullptr;

  return factory->create(parent);
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