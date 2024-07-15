/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/factory/node_properties_factory.h"

#include "flow_document/component/properties/node_properties.h"
#include "flow_document/flow/node.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------- NodePropertiesFactory ------------------------ */

NodePropertiesFactory::NodePropertiesFactory(QObject* parent)
    : ObjectPropertiesFactory(parent) {}

ObjectProperties* NodePropertiesFactory::create(QObject* parent) const {
  return new NodeProperties(parent);
}

QString NodePropertiesFactory::getObjectClassName() const {
  return Node::sGetClassName();
}

}  // namespace flow_document