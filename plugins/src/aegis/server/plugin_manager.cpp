/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/plugin_manager.h"

#include "aegis/server/server.h"
#include "aegis/server/sniffer.h"
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
    : m_server(new Server(this)), m_sniffer(new Sniffer(this)) {}

PluginManager::~PluginManager() = default;

Server* PluginManager::getServer() const { return m_server; }

Sniffer* PluginManager::getSniffer() const { return m_sniffer; }

}  // namespace aegis
