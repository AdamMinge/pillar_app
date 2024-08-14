/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/plugin_manager.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

std::unique_ptr<PluginManager> PluginManager::m_instance =
    std::unique_ptr<PluginManager>(nullptr);

PluginManager& PluginManager::getInstance() {
  if (!m_instance) m_instance.reset(new PluginManager);

  return *m_instance;
}

void PluginManager::deleteInstance() { m_instance.reset(nullptr); }

PluginManager::PluginManager()
    : m_server(new Server(this)),
      m_sniffer(new Sniffer(this)),
      m_searcher(new Searcher(this)),
      m_serializer(new Serializer(Serializer::Format::Json, this)),
      m_command_executor(new CommandExecutor(this)) {}

PluginManager::~PluginManager() = default;

Server* PluginManager::getServer() const { return m_server; }

Sniffer* PluginManager::getSniffer() const { return m_sniffer; }

Searcher* PluginManager::getSearcher() const { return m_searcher; }

Serializer* PluginManager::getSerializer() const { return m_serializer; }

CommandExecutor* PluginManager::getCommandExecutor() const {
  return m_command_executor;
}

}  // namespace aegis
