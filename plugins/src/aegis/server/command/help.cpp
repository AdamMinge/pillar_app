/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/help.h"

#include "aegis/server/plugin_manager.h"
#include "aegis/server/serializer.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* --------------------------------- HelpGetter ----------------------------- */

HelpGetter::HelpGetter() = default;

HelpGetter::~HelpGetter() = default;

Response<CommandsHelpMessage> HelpGetter::helps() {
  auto message = CommandsHelpMessage{};

  for (const auto command : commandExecutor()->getCommands()) {
    message.helps.insert(command->getName(), command->getHelp());
  }

  return message;
}

Response<CommandsListMessage> HelpGetter::commands() {
  auto message = CommandsListMessage{};

  for (const auto command : commandExecutor()->getCommands()) {
    message.commands.append(command->getName());
  }

  return message;
}

/* ------------------------------ ParentCommand ----------------------------- */

HelpCommand::HelpCommand() : Command(QLatin1String("Help")) {
  m_parser.addOptions({{{"d", "details"}, "Display details for each command"}});
}

HelpCommand::~HelpCommand() = default;

QByteArray HelpCommand::exec() {
  if (m_parser.isSet("details")) {
    return serializer()->serialize(m_help_getter.helps());
  } else {
    return serializer()->serialize(m_help_getter.commands());
  }
}

}  // namespace aegis
