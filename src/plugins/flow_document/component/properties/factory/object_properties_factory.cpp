/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/factory/object_properties_factory.h"

#include "flow_document/component/properties/object_properties.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/node.h"
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
  return Layer::getStaticClassName();
}

/* --------------------------- NodePropertiesFactory ------------------------ */

NodePropertiesFactory::NodePropertiesFactory(QObject* parent)
    : ObjectPropertiesFactory(parent) {}

ObjectProperties* NodePropertiesFactory::create(QObject* parent) const {
  return new NodeProperties(parent);
}

QString NodePropertiesFactory::getObjectClassName() const {
  return Node::getStaticClassName();
}

}  // namespace flow_document