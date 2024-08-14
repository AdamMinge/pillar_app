/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/keyboard_click.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseClickCommand -------------------------- */

KeyboardClickCommand::KeyboardClickCommand()
    : Command(QLatin1String("KeyboardClick")) {}

KeyboardClickCommand::~KeyboardClickCommand() = default;

QByteArray KeyboardClickCommand::exec() {
  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serializer()->serialize(error);
}

}  // namespace aegis
