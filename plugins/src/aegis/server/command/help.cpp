/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/help.h"

#include <aegis/server/command/executor.h>
#include <aegis/server/serializer.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* --------------------------------- HelpGetter ----------------------------- */

HelpGetter::HelpGetter() = default;

HelpGetter::~HelpGetter() = default;

Response<CommandsHelpMessage> HelpGetter::helps(
    const CommandExecutor& executor) {
  auto message = CommandsHelpMessage{};
  for (const auto command : executor.getCommands()) {
    message.helps.insert(command->getName(), command->getHelp());
  }

  return message;
}

Response<CommandsListMessage> HelpGetter::commands(
    const CommandExecutor& executor) {
  auto message = CommandsListMessage{};
  for (const auto command : executor.getCommands()) {
    message.commands.append(command->getName());
  }

  return message;
}

/* ------------------------------ ParentCommand ----------------------------- */

HelpCommand::HelpCommand(const CommandExecutor& executor)
    : Command(QLatin1String("Help"), executor) {
  m_parser.addOptions({{{"d", "details"}, "Display details for each command"}});
}

HelpCommand::~HelpCommand() = default;

QByteArray HelpCommand::exec() {
  const auto serialize = [this](auto object) {
    return getExecutor().getSerializer().serialize(object);
  };

  if (m_parser.isSet("details")) {
    return serialize(m_help_getter.helps(getExecutor()));
  } else {
    return serialize(m_help_getter.commands(getExecutor()));
  }
}

}  // namespace aegis
