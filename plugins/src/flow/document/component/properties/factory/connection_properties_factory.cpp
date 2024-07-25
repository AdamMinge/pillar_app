/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/properties/factory/connection_properties_factory.h"

#include "flow/document/component/properties/connection_properties.h"
#include "flow/document/flow/connection.h"
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------ ConnectionPropertiesFactory --------------------- */

ConnectionPropertiesFactory::ConnectionPropertiesFactory(QObject* parent)
    : ObjectPropertiesFactory(parent) {}

ObjectProperties* ConnectionPropertiesFactory::create(QObject* parent) const {
  return new ConnectionProperties(parent);
}

QString ConnectionPropertiesFactory::getObjectClassName() const {
  return Connection::sGetClassName();
}

}  // namespace flow