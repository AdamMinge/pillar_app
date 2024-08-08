/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/keyboard_click.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/executor.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

static constexpr QLatin1String keyboard_click_error =
    QLatin1String("Keyboard Click Command Error");

/* ----------------------------- MouseClickCommand -------------------------- */

KeyboardClickCommand::KeyboardClickCommand(const CommandExecutor &manager)
    : Command(manager) {
  m_parser.addHelpOption();
}

KeyboardClickCommand::~KeyboardClickCommand() = default;

QString KeyboardClickCommand::getName() const {
  return QString("KeyboardClick");
}

QByteArray KeyboardClickCommand::exec(const QStringList &args) {
  const auto serialize = [this](auto object) {
    return getManager().getSerializer().serialize(object);
  };

  if (!m_parser.parse(args)) {
    auto error =
        Response<>(ErrorMessage(keyboard_click_error, m_parser.errorText()));
    return serialize(error);
  }

  auto error = Response<>(ErrorMessage(
      keyboard_click_error, "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
