#ifndef AEGIS_SNIFFER_COMMAND_PLUGIN_H
#define AEGIS_SNIFFER_COMMAND_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/factory/utils.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/sniffer_command/command/sniffer.h"
#include "aegis/sniffer_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class LIB_AEGIS_SNIFFER_COMMAND_API SnifferCommandPlugin
    : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.pillar.PluginInterface" FILE "plugin.json")

 public:
  explicit SnifferCommandPlugin();
  ~SnifferCommandPlugin() override;

  void init() override;
};

DECLARE_COMMAND_FACTORY(LIB_AEGIS_SNIFFER_COMMAND_API, SnifferCommand)

}  // namespace aegis

#endif  // AEGIS_SNIFFER_COMMAND_PLUGIN_H
