/* ----------------------------------- Local -------------------------------- */
#include "shape_layer_plugin.h"
/* -------------------------------------------------------------------------- */

ShapeLayerPlugin::ShapeLayerPlugin() = default;

ShapeLayerPlugin::~ShapeLayerPlugin() = default;

void ShapeLayerPlugin::init() {
  addObject(new ShapeLayerFactory(tr("Shape Layer"), tr("Shape"), this));

  addObject(new ShapeLayerItemFactory(this));
  addObject(new ShapeItemFactory(this));
}
