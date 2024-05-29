/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/factory/layer_properties_factory.h"

#include "flow_document/component/properties/layer_properties.h"
#include "flow_document/flow/layer.h"
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------- LayerPropertiesFactory ----------------------- */

LayerPropertiesFactory::LayerPropertiesFactory(QObject* parent)
    : ObjectPropertiesFactory(parent) {}

ObjectProperties* LayerPropertiesFactory::create(QObject* parent) const {
  return new LayerProperties(parent);
}

QString LayerPropertiesFactory::getObjectClassName() const {
  return Layer::sGetClassName();
}

}  // namespace flow_document