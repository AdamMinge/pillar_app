#ifndef AEGIS_SERVER_SNIFFER_SNIFFER_H
#define AEGIS_SERVER_SNIFFER_SNIFFER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class Sniffer : public QObject {
  Q_OBJECT

 public:
  Sniffer(QObject *parent = nullptr);
  ~Sniffer() override;

 protected:
  bool eventFilter(QObject *object, QEvent *event) override;

 private:
  QObject *m_last_object;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_SNIFFER_SNIFFER_H