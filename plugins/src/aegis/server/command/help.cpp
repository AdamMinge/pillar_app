/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/help.h"

#include "aegis/server/plugin_manager.h"
#include "aegis/server/serializer.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ------------------------------ ParentCommand ----------------------------- */

HelpCommand::HelpCommand() : Command(QLatin1String("Help")) {
  m_parser.addOptions({{{"d", "details"}, "Display details for each command"}});
}

HelpCommand::~HelpCommand() = default;

QByteArray HelpCommand::exec() {
  if (m_parser.isSet("details")) {
    return serializer()->serialize(helps());
  } else {
    return serializer()->serialize(commands());
  }
}

Response<CommandsHelpMessage> HelpCommand::helps() {
  auto message = CommandsHelpMessage{};

  for (const auto command : commandExecutor()->getCommands()) {
    message.helps.insert(command->getName(), command->getHelp());
  }

  return message;
}

Response<CommandsListMessage> HelpCommand::commands() {
  auto message = CommandsListMessage{};

  for (const auto command : commandExecutor()->getCommands()) {
    message.commands.append(command->getName());
  }

  return message;
}

}  // namespace aegis
