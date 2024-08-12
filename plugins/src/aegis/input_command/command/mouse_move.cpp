/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/mouse_move.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/executor.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseMoveCommand --------------------------- */

MouseMoveCommand::MouseMoveCommand(const CommandExecutor &manager)
    : Command(QLatin1String("MouseMove"), manager) {}

MouseMoveCommand::~MouseMoveCommand() = default;

QByteArray MouseMoveCommand::exec() {
  const auto serialize = [this](auto object) {
    return getExecutor().getSerializer().serialize(object);
  };

  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
