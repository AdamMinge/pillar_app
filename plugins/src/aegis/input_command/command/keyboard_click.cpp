/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/keyboard_click.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/executor.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseClickCommand -------------------------- */

KeyboardClickCommand::KeyboardClickCommand(const CommandExecutor &manager)
    : Command(QLatin1String("KeyboardClick"), manager) {}

KeyboardClickCommand::~KeyboardClickCommand() = default;

QByteArray KeyboardClickCommand::exec() {
  const auto serialize = [this](auto object) {
    return getExecutor().getSerializer().serialize(object);
  };

  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
