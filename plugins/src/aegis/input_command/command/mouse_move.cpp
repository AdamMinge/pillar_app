/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/mouse_move.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/executor.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseMoveCommand --------------------------- */

MouseMoveCommand::MouseMoveCommand(const CommandExecutor &manager)
    : Command(manager) {}

MouseMoveCommand::~MouseMoveCommand() = default;

QString MouseMoveCommand::getName() const { return QString("MouseMove"); }

QList<QCommandLineOption> MouseMoveCommand::getOptions() const { return {}; }

QByteArray MouseMoveCommand::exec(const QCommandLineParser &parser) {
  const auto serialize = [this](auto object) {
    return getExecutor().getSerializer().serialize(object);
  };

  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
