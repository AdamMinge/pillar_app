/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/keyboard_click.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/executor.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseClickCommand -------------------------- */

KeyboardClickCommand::KeyboardClickCommand(const CommandExecutor &manager)
    : Command(manager) {}

KeyboardClickCommand::~KeyboardClickCommand() = default;

QString KeyboardClickCommand::getName() const {
  return QString("KeyboardClick");
}

QList<QCommandLineOption> KeyboardClickCommand::getOptions() const {
  return {};
}

QByteArray KeyboardClickCommand::exec(const QCommandLineParser &parser) {
  const auto serialize = [this](auto object) {
    return getExecutor().getSerializer().serialize(object);
  };

  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
