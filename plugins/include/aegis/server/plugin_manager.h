#ifndef AEGIS_SERVER_SERVER_MANAGER_H
#define AEGIS_SERVER_SERVER_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTcpServer>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class Server;
class Sniffer;

class LIB_AEGIS_SERVER_API PluginManager : public QObject {
  Q_OBJECT

 public:
  [[nodiscard]] static PluginManager& getInstance();
  static void deleteInstance();

 public:
  ~PluginManager() override;

  [[nodiscard]] Server* getServer() const;
  [[nodiscard]] Sniffer* getSniffer() const;

 protected:
  explicit PluginManager();

 private:
  static std::unique_ptr<PluginManager> m_instance;

  Server* m_server;
  Sniffer* m_sniffer;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_SERVER_MANAGER_H