/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/command/mouse_click.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/executor.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

static constexpr QLatin1String mouse_click_error =
    QLatin1String("Mouse Click Command Error");

/* ----------------------------- MouseClickCommand -------------------------- */

MouseClickCommand::MouseClickCommand(const CommandExecutor &manager)
    : Command(manager) {
  m_parser.addHelpOption();
}

MouseClickCommand::~MouseClickCommand() = default;

QString MouseClickCommand::getName() const { return QString("MouseClick"); }

QByteArray MouseClickCommand::exec(const QStringList &args) {
  const auto serialize = [this](auto object) {
    return getManager().getSerializer().serialize(object);
  };

  if (!m_parser.parse(args)) {
    auto error =
        Response<>(ErrorMessage(mouse_click_error, m_parser.errorText()));
    return serialize(error);
  }

  auto error = Response<>(ErrorMessage(
      mouse_click_error, "At least one of options must be provided."));
  return serialize(error);
}

}  // namespace aegis
