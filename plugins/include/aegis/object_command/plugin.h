#ifndef AEGIS_OBJECT_COMMAND_PLUGIN_H
#define AEGIS_OBJECT_COMMAND_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/factory/utils.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class LIB_AEGIS_OBJECT_COMMAND_API ObjectCommandPlugin
    : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.pillar.PluginInterface" FILE "plugin.json")

 public:
  explicit ObjectCommandPlugin();
  ~ObjectCommandPlugin() override;

  void init() override;
};

}  // namespace aegis

#endif  // AEGIS_OBJECT_COMMAND_PLUGIN_H
