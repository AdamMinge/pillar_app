/* ----------------------------------- Local -------------------------------- */
#include "shape_layer_plugin.h"
/* -------------------------------------------------------------------------- */

ShapeLayerPlugin::ShapeLayerPlugin() = default;

ShapeLayerPlugin::~ShapeLayerPlugin() = default;

void ShapeLayerPlugin::init() {
  addObject(new ShapeLayerFactory(tr("Shape Layer"), tr("Shape"), this));

  addObject(new ShapeLayerGraphicsItemFactory(this));
  addObject(new ShapeGraphicsItemFactory(this));
}
