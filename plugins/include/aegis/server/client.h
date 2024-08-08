#ifndef AEGIS_SERVER_CLIENT_H
#define AEGIS_SERVER_CLIENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTcpSocket>
#include <QThread>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class CommandExecutor;

/* -------------------------------- ClientThread ---------------------------- */

class LIB_AEGIS_SERVER_API ClientThread : public QThread {
  Q_OBJECT

 public:
  ClientThread(qintptr socket_descriptor, QObject* parent = nullptr);
  ~ClientThread();

 protected:
  void run() override;

 private:
  qintptr m_socket_descriptor;
};

/* ------------------------------- ClientHandler ---------------------------- */

class LIB_AEGIS_SERVER_API ClientHandler : public QObject {
  Q_OBJECT

 public:
  explicit ClientHandler(qintptr socket_descriptor, QObject* parent = nullptr);
  ~ClientHandler() override;

 signals:
  void error(QTcpSocket::SocketError socketError);
  void finished();

 public slots:
  void readyRead();
  void disconnected();

 private:
  std::unique_ptr<QTcpSocket> m_socket;
  std::unique_ptr<CommandExecutor> m_command_manager;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_CLIENT_H