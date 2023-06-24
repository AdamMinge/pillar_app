#ifndef SHAPE_LAYER_PLUGIN_H
#define SHAPE_LAYER_PLUGIN_H

/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/scene/item/factory/graphics_item_factory.h>
#include <flow_document/flow/factory/layer_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "component/scene/item/shape_graphics_item.h"
#include "component/scene/item/shape_layer_graphics_item.h"
#include "export.h"
#include "flow/shape.h"
#include "flow/shape_layer.h"
/* -------------------------------------------------------------------------- */

class SHAPE_API ShapeLayerPlugin : public egnite::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(egnite::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit ShapeLayerPlugin();
  ~ShapeLayerPlugin() override;

  void init() override;
};

DECLARE_LAYER_FACTORY(SHAPE_API, ShapeLayer)

DECLARE_GRAPHICS_ITEM_FACTORY(SHAPE_API, ShapeLayerGraphicsItem, ShapeLayer)
DECLARE_GRAPHICS_ITEM_FACTORY(SHAPE_API, ShapeGraphicsItem, Shape)

#endif  // SHAPE_LAYER_PLUGIN_H
