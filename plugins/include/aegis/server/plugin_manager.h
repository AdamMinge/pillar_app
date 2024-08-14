#ifndef AEGIS_SERVER_SERVER_MANAGER_H
#define AEGIS_SERVER_SERVER_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTcpServer>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/executor.h"
#include "aegis/server/export.h"
#include "aegis/server/search/searcher.h"
#include "aegis/server/serializer.h"
#include "aegis/server/server.h"
#include "aegis/server/sniffer.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class LIB_AEGIS_SERVER_API PluginManager : public QObject {
  Q_OBJECT

 public:
  [[nodiscard]] static PluginManager& getInstance();
  static void deleteInstance();

 public:
  ~PluginManager() override;

  [[nodiscard]] Server* getServer() const;
  [[nodiscard]] Sniffer* getSniffer() const;
  [[nodiscard]] Searcher* getSearcher() const;
  [[nodiscard]] Serializer* getSerializer() const;
  [[nodiscard]] CommandExecutor* getCommandExecutor() const;

 protected:
  explicit PluginManager();

 private:
  static std::unique_ptr<PluginManager> m_instance;

  Server* m_server;
  Sniffer* m_sniffer;
  Searcher* m_searcher;
  Serializer* m_serializer;
  CommandExecutor* m_command_executor;
};

inline Server* server() { return PluginManager::getInstance().getServer(); }

inline Sniffer* sniffer() { return PluginManager::getInstance().getSniffer(); }

inline Searcher* searcher() {
  return PluginManager::getInstance().getSearcher();
}

inline Serializer* serializer() {
  return PluginManager::getInstance().getSerializer();
}

inline CommandExecutor* commandExecutor() {
  return PluginManager::getInstance().getCommandExecutor();
}

}  // namespace aegis

#endif  // AEGIS_SERVER_SERVER_MANAGER_H