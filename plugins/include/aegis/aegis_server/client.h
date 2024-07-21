#ifndef AEGIS_SERVER_CLIENT_H
#define AEGIS_SERVER_CLIENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMap>
#include <QRunnable>
#include <QScopedPointer>
#include <QTcpSocket>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <unordered_map>
/* ----------------------------------- Local -------------------------------- */
#include "aegis_server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class Serializer;

}  // namespace aegis

namespace aegis_server {

class Command;

class LIB_AEGIS_SERVER_API Client : public QRunnable {
 public:
  explicit Client(qintptr socket_descriptor);

  void run() override;

 private:
  void initCommands();
  void processRequest(const QByteArray& data);
  void sendResponse(const QByteArray& data);

 private:
  qintptr m_socket_descriptor;
  std::unique_ptr<QTcpSocket> m_socket;
  std::unordered_map<QString, std::unique_ptr<Command>> m_commands;
  std::unique_ptr<aegis::Serializer> m_serializer;
};

}  // namespace aegis_server

#endif  // AEGIS_SERVER_CLIENT_H