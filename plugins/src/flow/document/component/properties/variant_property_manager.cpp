/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/properties/variant_property_manager.h"
/* -------------------------------------------------------------------------- */

namespace flow {

VariantPropertyManager::VariantPropertyManager(QObject *parent)
    : qtils::QtVariantPropertyManager(parent) {}

VariantPropertyManager::~VariantPropertyManager() = default;

}  // namespace flow