/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/variant_property_manager.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

VariantPropertyManager::VariantPropertyManager(QObject *parent)
    : utils::QtVariantPropertyManager(parent) {}

VariantPropertyManager::~VariantPropertyManager() = default;

}  // namespace flow_document