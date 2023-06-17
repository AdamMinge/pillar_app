/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/factory/layer_factory.h"

#include "flow_document/flow/layer.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

LayerFactory::LayerFactory(QString name)
    : Factory(Type::LayerFactory, std::move(name)) {}

LayerFactory::~LayerFactory() = default;

}  // namespace flow_document