/* ----------------------------------- Local -------------------------------- */
#include "aegis/user_input_command/command/keyboard_click.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseClickCommand -------------------------- */

KeyboardClickCommand::KeyboardClickCommand(const ResponseSerializer &serializer)
    : Command(serializer) {
  m_parser.addHelpOption();
}

KeyboardClickCommand::~KeyboardClickCommand() = default;

QString KeyboardClickCommand::getName() const {
  return QString("KeyboardClick");
}

QByteArray KeyboardClickCommand::exec(const QStringList &args) {
  if (m_parser.parse(args)) {
    return serialize(Response<>(EmptyMessage()));
  }

  auto error = Response<>(ErrorMessage(QLatin1String("Recorder Command Error"),
                                       m_parser.errorText()));
  return serialize(error);
}

}  // namespace aegis
