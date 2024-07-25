/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/properties/factory/object_properties_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* -------------------------- ObjectPropertiesFactory ----------------------- */

ObjectPropertiesFactory::ObjectPropertiesFactory(QObject* parent)
    : QObject(parent) {}

ObjectPropertiesFactory::~ObjectPropertiesFactory() = default;

}  // namespace flow