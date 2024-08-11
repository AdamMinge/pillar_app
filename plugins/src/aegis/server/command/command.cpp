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

Command::Command(const CommandExecutor& executor) : m_executor(executor) {}

Command::~Command() = default;

QByteArray Command::exec(const QStringList& args) {
  const auto serialize = [this](auto object) {
    return getExecutor().getSerializer().serialize(object);
  };

  auto parser = QCommandLineParser{};
  auto help_option = parser.addHelpOption();
  parser.addOptions(getOptions());

  if (!parser.parse(args)) {
    auto error = Response<>(ErrorMessage(getError(), parser.errorText()));
    return serialize(error);
  }

  if (parser.isSet(help_option)) {
    auto help = Response<HelpMessage>(HelpMessage(getHelp(parser)));
    return serialize(help);
  }

  return exec(parser);
}

QString Command::getError() const {
  return QLatin1String("%1 Command Error").arg(getName());
}

const CommandExecutor& Command::getExecutor() const { return m_executor; }

QString Command::getHelp(const QCommandLineParser& parser) const {
  auto help_text = parser.helpText();
  const auto options_index = help_text.indexOf("Options:");

  if (options_index != -1) {
    help_text = help_text.mid(options_index);
  }

  auto help_lines = help_text.split('\n');
  help_lines.erase(std::remove_if(help_lines.begin(), help_lines.end(),
                                  [](const QString& line) {
                                    return line.contains("--help-all");
                                  }),
                   help_lines.end());

  help_text = help_lines.join('\n');

  return help_text;
}

}  // namespace aegis
