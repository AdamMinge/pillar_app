/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/mouse_move.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/executor.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

static constexpr QLatin1String mouse_move_error =
    QLatin1String("Mouse Move Command Error");

/* ----------------------------- MouseMoveCommand --------------------------- */

MouseMoveCommand::MouseMoveCommand(const CommandExecutor &manager)
    : Command(manager) {
  m_parser.addHelpOption();
}

MouseMoveCommand::~MouseMoveCommand() = default;

QString MouseMoveCommand::getName() const { return QString("MouseMove"); }

QByteArray MouseMoveCommand::exec(const QStringList &args) {
  const auto serialize = [this](auto object) {
    return getManager().getSerializer().serialize(object);
  };

  if (!m_parser.parse(args)) {
    auto error =
        Response<>(ErrorMessage(mouse_move_error, m_parser.errorText()));
    return serialize(error);
  }

  auto error = Response<>(ErrorMessage(
      mouse_move_error, "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
