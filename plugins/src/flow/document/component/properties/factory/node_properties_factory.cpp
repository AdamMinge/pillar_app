/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/properties/factory/node_properties_factory.h"

#include "flow/document/component/properties/node_properties.h"
#include "flow/document/flow/node.h"
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* --------------------------- NodePropertiesFactory ------------------------ */

NodePropertiesFactory::NodePropertiesFactory(QObject* parent)
    : ObjectPropertiesFactory(parent) {}

ObjectProperties* NodePropertiesFactory::create(QObject* parent) const {
  return new NodeProperties(parent);
}

QString NodePropertiesFactory::getObjectClassName() const {
  return Node::sGetClassName();
}

}  // namespace flow