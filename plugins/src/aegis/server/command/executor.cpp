/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/executor.h"

#include "aegis/server/command/command.h"
#include "aegis/server/command/factory/factory.h"
#include "aegis/server/response.h"
#include "aegis/server/serializer.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ------------------------------- CommandExecutor -------------------------- */

CommandExecutor::CommandExecutor()
    : m_serializer(std::make_unique<ResponseSerializer>(
          ResponseSerializer::Format::Json)) {
  loadObjects();
}

CommandExecutor::~CommandExecutor() = default;

QByteArray CommandExecutor::exec(const QByteArray& data) {
  const auto splited_data = data.split(' ');
  const auto command_name = splited_data.front();

  auto response = QByteArray{};
  if (auto iter = m_commands.find(command_name); iter != m_commands.end()) {
    auto args = QStringList{};
    std::transform(splited_data.constBegin(), splited_data.constEnd(),
                   std::back_inserter(args),
                   [](const auto& data) { return QString::fromUtf8(data); });

    response = (*iter).second->exec(args);
  } else {
    auto error = Response<>(ErrorMessage(
        QLatin1String("Process Request Error"),
        QLatin1String("Cannot find command: %1").arg(command_name)));
    response = m_serializer->serialize(error);
  }

  return response;
}

const ResponseSerializer& CommandExecutor::getSerializer() const {
  return *m_serializer;
}

void CommandExecutor::addedObject(CommandFactory* factory) {
  auto command = factory->create(*this);

  m_commands.insert(std::make_pair(command->getName(), command.get()));
  m_command_by_factory.insert(std::make_pair(factory, std::move(command)));
}

void CommandExecutor::removedObject(CommandFactory* factory) {
  if (m_command_by_factory.contains(factory)) {
    auto& command = m_command_by_factory[factory];

    m_commands.erase(command->getName());
    m_command_by_factory.erase(factory);
  }
}

}  // namespace aegis
