/* ----------------------------------- Local -------------------------------- */
#include "aegis/user_input_command/command/mouse_click.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseClickCommand -------------------------- */

MouseClickCommand::MouseClickCommand(const ResponseSerializer &serializer)
    : Command(serializer) {
  m_parser.addHelpOption();
}

MouseClickCommand::~MouseClickCommand() = default;

QString MouseClickCommand::getName() const { return QString("MouseClick"); }

QByteArray MouseClickCommand::exec(const QStringList &args) {
  if (m_parser.parse(args)) {
    return serialize(Response<>(EmptyMessage()));
  }

  auto error = Response<>(ErrorMessage(QLatin1String("Recorder Command Error"),
                                       m_parser.errorText()));
  return serialize(error);
}

}  // namespace aegis
