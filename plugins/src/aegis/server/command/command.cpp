/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/command.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/executor.h>
#include <aegis/server/response.h>
#include <aegis/server/serializer.h>
/* ------------------------------------ Qt ---------------------------------- */
#include <QCommandLineParser>
/* -------------------------------------------------------------------------- */

namespace aegis {

Command::Command(const QString& name, const CommandExecutor& executor)
    : m_name(name), m_executor(executor) {
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

const CommandExecutor& Command::getExecutor() const { return m_executor; }

QByteArray Command::exec(const QStringList& args) {
  const auto serialize = [this](auto object) {
    return getExecutor().getSerializer().serialize(object);
  };

  if (!m_parser.parse(args)) {
    auto error = Response<>(ErrorMessage(getError(), m_parser.errorText()));
    return serialize(error);
  }

  if (m_parser.isSet("help")) {
    auto help = Response<HelpMessage>(HelpMessage(getHelp()));
    return serialize(help);
  }

  return exec();
}

}  // namespace aegis
