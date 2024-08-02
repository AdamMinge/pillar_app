/* ----------------------------------- Local -------------------------------- */
#include "aegis/sniffer_command/command/sniffer.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/manager.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

static constexpr QLatin1String sniffer_error =
    QLatin1String("Sniffer Command Error");

/* ------------------------------ RecorderCommand --------------------------- */

SnifferCommand::SnifferCommand(const CommandManager& manager)
    : Command(manager) {
  m_parser.addHelpOption();
  m_parser.addOptions({
      {{"s", "start"}, "Start the Sniffer"},
      {{"t", "stop"}, "Stop the Sniffer"},
  });
}

SnifferCommand::~SnifferCommand() = default;

QString SnifferCommand::getName() const { return QString("Sniffer"); }

QByteArray SnifferCommand::exec(const QStringList& args) {
  const auto serialize = [this](auto object) {
    return getManager().getSerializer().serialize(object);
  };

  if (m_parser.parse(args)) {
    if (m_parser.isSet("start"))
      ;
    if (m_parser.isSet("stop"))
      ;
  }

  auto error = Response<>(ErrorMessage(sniffer_error, m_parser.errorText()));
  return serialize(error);
}

}  // namespace aegis
