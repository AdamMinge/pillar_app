/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/factory/connection_properties_factory.h"

#include "flow_document/component/properties/connection_properties.h"
#include "flow_document/flow/connection.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ------------------------ ConnectionPropertiesFactory --------------------- */

ConnectionPropertiesFactory::ConnectionPropertiesFactory(QObject* parent)
    : ObjectPropertiesFactory(parent) {}

ObjectProperties* ConnectionPropertiesFactory::create(QObject* parent) const {
  return new ConnectionProperties(parent);
}

QString ConnectionPropertiesFactory::getObjectClassName() const {
  return Connection::sGetClassName();
}

}  // namespace flow_document