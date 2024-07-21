#ifndef AEGIS_SERVER_COMMAND_COMMAND_H
#define AEGIS_SERVER_COMMAND_COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QByteArray>
/* ----------------------------------- Aegis -------------------------------- */
#include <aegis/serializer.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis_server/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {
class OArchive;
}

namespace aegis_server {

/* ---------------------------------- Command ------------------------------- */

class LIB_AEGIS_SERVER_API Command {
 public:
  explicit Command(const aegis::Serializer& serializer);
  virtual ~Command();

  [[nodiscard]] virtual QByteArray exec(const QStringList& args) = 0;

 protected:
  template <typename TYPE>
  [[nodiscard]] QByteArray serialize(const TYPE& data);

 private:
  const aegis::Serializer& m_serializer;
};

template <typename TYPE>
QByteArray Command::serialize(const TYPE& data) {
  return m_serializer.serialize(data);
}

}  // namespace aegis_server

#endif  // AEGIS_SERVER_COMMAND_COMMAND_H