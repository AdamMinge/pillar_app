#ifndef AEGIS_SERVER_SERVER_H
#define AEGIS_SERVER_SERVER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTcpServer>
/* ----------------------------------- Local -------------------------------- */
#include "aegis_server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis_server {

class LIB_AEGIS_SERVER_API Server : public QTcpServer {
  Q_OBJECT
 public:
  explicit Server(QObject *parent = nullptr);

  bool start(quint16 port);

 protected:
  void incomingConnection(qintptr socketDescriptor) override;
};

}  // namespace aegis_server

#endif  // AEGIS_SERVER_SERVER_H