/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/mouse_move.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseMoveCommand --------------------------- */

MouseMoveCommand::MouseMoveCommand() : Command(QLatin1String("MouseMove")) {}

MouseMoveCommand::~MouseMoveCommand() = default;

QByteArray MouseMoveCommand::exec() {
  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serializer()->serialize(error);
}

}  // namespace aegis
