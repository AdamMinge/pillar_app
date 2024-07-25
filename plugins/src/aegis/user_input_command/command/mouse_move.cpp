/* ----------------------------------- Local -------------------------------- */
#include "aegis/user_input_command/command/mouse_move.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseMoveCommand --------------------------- */

MouseMoveCommand::MouseMoveCommand(const ResponseSerializer &serializer)
    : Command(serializer) {
  m_parser.addHelpOption();
}

MouseMoveCommand::~MouseMoveCommand() = default;

QString MouseMoveCommand::getName() const { return QString("MouseMove"); }

QByteArray MouseMoveCommand::exec(const QStringList &args) {
  if (m_parser.parse(args)) {
    return serialize(Response<>(EmptyMessage()));
  }

  auto error = Response<>(ErrorMessage(QLatin1String("Recorder Command Error"),
                                       m_parser.errorText()));
  return serialize(error);
}

}  // namespace aegis
