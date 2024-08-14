/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/mouse_click.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseClickCommand -------------------------- */

MouseClickCommand::MouseClickCommand() : Command(QLatin1String("MouseClick")) {}

MouseClickCommand::~MouseClickCommand() = default;

QByteArray MouseClickCommand::exec() {
  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serializer()->serialize(error);
}

}  // namespace aegis
