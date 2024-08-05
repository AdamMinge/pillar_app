/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/plugin.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

InputCommandPlugin::InputCommandPlugin() = default;

InputCommandPlugin::~InputCommandPlugin() = default;

void InputCommandPlugin::init() {
  addObject(new KeyboardClickCommandFactory(this));
  addObject(new MouseClickCommandFactory(this));
  addObject(new MouseMoveCommandFactory(this));
}

}  // namespace aegis