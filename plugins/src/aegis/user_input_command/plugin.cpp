/* ----------------------------------- Local -------------------------------- */
#include "aegis/user_input_command/plugin.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

UserInputCommandPlugin::UserInputCommandPlugin() = default;

UserInputCommandPlugin::~UserInputCommandPlugin() = default;

void UserInputCommandPlugin::init() {
  addObject(new KeyboardClickCommandFactory(this));
  addObject(new MouseClickCommandFactory(this));
  addObject(new MouseMoveCommandFactory(this));
}

}  // namespace aegis