#ifndef AEGIS_SEARCH_COMMAND_PLUGIN_H
#define AEGIS_SEARCH_COMMAND_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/factory/utils.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/search_command/command/find.h"
#include "aegis/search_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class LIB_AEGIS_SEARCH_COMMAND_API SnifferCommandPlugin
    : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.pillar.PluginInterface" FILE "plugin.json")

 public:
  explicit SnifferCommandPlugin();
  ~SnifferCommandPlugin() override;

  void init() override;
};

DECLARE_COMMAND_FACTORY(LIB_AEGIS_SEARCH_COMMAND_API, FindCommand)

}  // namespace aegis

#endif  // AEGIS_SEARCH_COMMAND_PLUGIN_H
