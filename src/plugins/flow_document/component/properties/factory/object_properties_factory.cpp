/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/factory/object_properties_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------- ObjectPropertiesFactory ----------------------- */

ObjectPropertiesFactory::ObjectPropertiesFactory(QObject* parent)
    : QObject(parent) {}

ObjectPropertiesFactory::~ObjectPropertiesFactory() = default;

}  // namespace flow_document