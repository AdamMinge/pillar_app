#ifndef AEGIS_SERVER_PLUGIN_H
#define AEGIS_SERVER_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/factory/utils.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/command/recorder.h"
#include "aegis/recorder_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class LIB_AEGIS_RECORDER_COMMAND_API RecorderCommandPlugin
    : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.pillar.PluginInterface" FILE "plugin.json")

 public:
  explicit RecorderCommandPlugin();
  ~RecorderCommandPlugin() override;

  void init() override;
};

DECLARE_COMMAND_FACTORY(LIB_AEGIS_RECORDER_COMMAND_API, RecorderCommand)

}  // namespace aegis

#endif  // AEGIS_SERVER_PLUGIN_H
