#ifndef AEGIS_SERVER_H
#define AEGIS_SERVER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTcpServer>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class LIB_AEGIS_API Server : public QTcpServer {
  Q_OBJECT
 public:
  explicit Server(QObject *parent = nullptr);

  bool start(quint16 port);

 protected:
  void incomingConnection(qintptr socketDescriptor) override;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_H