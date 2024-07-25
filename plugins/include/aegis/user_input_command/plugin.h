#ifndef AEGIS_SERVER_PLUGIN_H
#define AEGIS_SERVER_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/factory/utils.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/user_input_command/command/keyboard_click.h"
#include "aegis/user_input_command/command/mouse_click.h"
#include "aegis/user_input_command/command/mouse_move.h"
#include "aegis/user_input_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class LIB_AEGIS_USER_INPUT_COMMAND_API UserInputCommandPlugin
    : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.pillar.PluginInterface" FILE "plugin.json")

 public:
  explicit UserInputCommandPlugin();
  ~UserInputCommandPlugin() override;

  void init() override;
};

DECLARE_COMMAND_FACTORY(LIB_AEGIS_USER_INPUT_COMMAND_API, KeyboardClickCommand)
DECLARE_COMMAND_FACTORY(LIB_AEGIS_USER_INPUT_COMMAND_API, MouseClickCommand)
DECLARE_COMMAND_FACTORY(LIB_AEGIS_USER_INPUT_COMMAND_API, MouseMoveCommand)

}  // namespace aegis

#endif  // AEGIS_SERVER_PLUGIN_H
