#ifndef AEGIS_SERVER_SERVER_H
#define AEGIS_SERVER_SERVER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTcpServer>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class ClientThread;

class LIB_AEGIS_SERVER_API Server : public QTcpServer {
  Q_OBJECT

 public:
  explicit Server(QObject* parent = nullptr);
  ~Server() override;

  bool start(const QHostAddress& host, quint16 port);
  void stop();

 protected:
  void incomingConnection(qintptr socketDescriptor) override;

 private:
  QList<ClientThread*> m_threads;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_SERVER_H