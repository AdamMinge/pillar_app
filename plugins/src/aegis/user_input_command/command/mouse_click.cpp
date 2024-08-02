/* ----------------------------------- Local -------------------------------- */
#include "aegis/user_input_command/command/mouse_click.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command_manager.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseClickCommand -------------------------- */

MouseClickCommand::MouseClickCommand(const CommandManager &manager)
    : Command(manager) {
  m_parser.addHelpOption();
}

MouseClickCommand::~MouseClickCommand() = default;

QString MouseClickCommand::getName() const { return QString("MouseClick"); }

QByteArray MouseClickCommand::exec(const QStringList &args) {
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
