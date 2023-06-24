#ifndef SHAPE_LAYER_PLUGIN_H
#define SHAPE_LAYER_PLUGIN_H

/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_interface.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
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

#endif  // SHAPE_LAYER_PLUGIN_H
