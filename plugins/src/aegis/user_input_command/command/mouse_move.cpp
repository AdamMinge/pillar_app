/* ----------------------------------- Local -------------------------------- */
#include "aegis/user_input_command/command/mouse_move.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command_manager.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseMoveCommand --------------------------- */

MouseMoveCommand::MouseMoveCommand(const CommandManager &manager)
    : Command(manager) {
  m_parser.addHelpOption();
}

MouseMoveCommand::~MouseMoveCommand() = default;

QString MouseMoveCommand::getName() const { return QString("MouseMove"); }

QByteArray MouseMoveCommand::exec(const QStringList &args) {
  const auto serialize = [this](auto object) {
    return getManager().getSerializer().serialize(object);
  };

  if (m_parser.parse(args)) {
    return serialize(Response<>(EmptyMessage()));
  }

  auto error = Response<>(ErrorMessage(QLatin1String("Recorder Command Error"),
                                       m_parser.errorText()));
  return serialize(error);
}

}  // namespace aegis
