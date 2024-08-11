/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/mouse_click.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/executor.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseClickCommand -------------------------- */

MouseClickCommand::MouseClickCommand(const CommandExecutor &manager)
    : Command(manager) {}

MouseClickCommand::~MouseClickCommand() = default;

QString MouseClickCommand::getName() const { return QString("MouseClick"); }

QList<QCommandLineOption> MouseClickCommand::getOptions() const { return {}; }

QByteArray MouseClickCommand::exec(const QCommandLineParser &parser) {
  const auto serialize = [this](auto object) {
    return getExecutor().getSerializer().serialize(object);
  };

  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
