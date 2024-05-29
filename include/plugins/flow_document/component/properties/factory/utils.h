#ifndef FLOW_DOCUMENT_PROPERTIES_FACTORY_UTILS_H
#define FLOW_DOCUMENT_PROPERTIES_FACTORY_UTILS_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/factory/object_properties_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Object;

/* ----------------------------------- Utils -------------------------------- */

[[nodiscard]] ObjectProperties* createObjectProperties(
    Object* object, QObject* parent = nullptr);

[[nodiscard]] ObjectPropertiesFactory* getObjectPropertiesFactoryObject(
    Object* object);

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_PROPERTIES_FACTORY_UTILS_H