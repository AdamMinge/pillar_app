/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/command.h"

#include "aegis/server/plugin_manager.h"
#include "aegis/server/response.h"
#include "aegis/server/serializer.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QCommandLineParser>
/* -------------------------------------------------------------------------- */

namespace aegis {

Command::Command(const QString& name) : m_name(name) {
  m_parser.addOptions({{{"h", "help"}, "Displays help for command."}});
}

Command::~Command() = default;

QString Command::getName() const { return m_name; }

QString Command::getError() const {
  return QLatin1String("%1 Command Error").arg(m_name);
}

QString Command::getHelp() const {
  auto help = m_parser.helpText();
  help.replace(qApp->arguments().constFirst(), m_name);

  return help;
}

QByteArray Command::exec(const QStringList& args) {
  if (!m_parser.parse(args)) {
    auto error = Response<>(ErrorMessage(getError(), m_parser.errorText()));
    return serializer()->serialize(error);
  }

  if (m_parser.isSet("help")) {
    auto help = Response<HelpMessage>(HelpMessage(getHelp()));
    return serializer()->serialize(help);
  }

  return exec();
}

}  // namespace aegis
