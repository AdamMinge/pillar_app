#ifndef AEGIS_SERVER_SERVER_MANAGER_H
#define AEGIS_SERVER_SERVER_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTcpServer>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class Server;

class LIB_AEGIS_SERVER_API ServerManager : public QObject {
  Q_OBJECT

 public:
  [[nodiscard]] static ServerManager& getInstance();
  static void deleteInstance();

 public:
  ~ServerManager() override;

  bool start(const QHostAddress& host, quint16 port);
  void stop();

  [[nodiscard]] bool isRunning() const;

  [[nodiscard]] QHostAddress getHost() const;
  [[nodiscard]] quint16 getPort() const;

 protected:
  explicit ServerManager();

 private:
  static std::unique_ptr<ServerManager> m_instance;

  Server* m_server;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_SERVER_MANAGER_H