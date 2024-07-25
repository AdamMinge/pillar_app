/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/server_manager.h"

#include "aegis/server/server.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

std::unique_ptr<ServerManager> ServerManager::m_instance =
    std::unique_ptr<ServerManager>(nullptr);

ServerManager& ServerManager::getInstance() {
  if (!m_instance) m_instance.reset(new ServerManager);

  return *m_instance;
}

void ServerManager::deleteInstance() { m_instance.reset(nullptr); }

ServerManager::ServerManager() : m_server(new Server(this)) {}

ServerManager::~ServerManager() = default;

bool ServerManager::start(const QHostAddress& host, quint16 port) {
  return m_server->start(host, port);
}

void ServerManager::stop() { m_server->stop(); }

}  // namespace aegis
