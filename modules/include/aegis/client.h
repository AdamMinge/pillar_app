#ifndef AEGIS_CLIENT_H
#define AEGIS_CLIENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMap>
#include <QRunnable>
#include <QScopedPointer>
#include <QTcpSocket>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <unordered_map>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class Command;
class Serializer;

class LIB_AEGIS_API Client : public QRunnable {
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
  std::unique_ptr<Serializer> m_serializer;
};

}  // namespace aegis

#endif  // AEGIS_CLIENT_H