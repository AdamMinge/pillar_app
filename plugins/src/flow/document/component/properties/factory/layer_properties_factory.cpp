/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/properties/factory/layer_properties_factory.h"

#include "flow/document/component/properties/layer_properties.h"
#include "flow/document/flow/layer.h"
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace flow {

/* --------------------------- LayerPropertiesFactory ----------------------- */

LayerPropertiesFactory::LayerPropertiesFactory(QObject* parent)
    : ObjectPropertiesFactory(parent) {}

ObjectProperties* LayerPropertiesFactory::create(QObject* parent) const {
  return new LayerProperties(parent);
}

QString LayerPropertiesFactory::getObjectClassName() const {
  return Layer::sGetClassName();
}

}  // namespace flow