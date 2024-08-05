#ifndef AEGIS_INPUT_COMMAND_PLUGIN_H
#define AEGIS_INPUT_COMMAND_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/factory/utils.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/keyboard_click.h"
#include "aegis/input_command/command/mouse_click.h"
#include "aegis/input_command/command/mouse_move.h"
#include "aegis/input_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class LIB_AEGIS_INPUT_COMMAND_API InputCommandPlugin
    : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.pillar.PluginInterface" FILE "plugin.json")

 public:
  explicit InputCommandPlugin();
  ~InputCommandPlugin() override;

  void init() override;
};

DECLARE_COMMAND_FACTORY(LIB_AEGIS_INPUT_COMMAND_API, KeyboardClickCommand)
DECLARE_COMMAND_FACTORY(LIB_AEGIS_INPUT_COMMAND_API, MouseClickCommand)
DECLARE_COMMAND_FACTORY(LIB_AEGIS_INPUT_COMMAND_API, MouseMoveCommand)

}  // namespace aegis

#endif  // AEGIS_INPUT_COMMAND_PLUGIN_H
