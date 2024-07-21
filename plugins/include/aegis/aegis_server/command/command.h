#ifndef AEGIS_SERVER_COMMAND_COMMAND_H
#define AEGIS_SERVER_COMMAND_COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QByteArray>
/* ----------------------------------- Local -------------------------------- */
#include "aegis_server/export.h"
#include "aegis_server/serializer.h"
/* -------------------------------------------------------------------------- */

namespace qtils {
class OArchive;
}

namespace aegis_server {

/* ---------------------------------- Command ------------------------------- */

class LIB_AEGIS_SERVER_API Command {
 public:
  explicit Command(const ResponseSerializer& serializer);
  virtual ~Command();

  [[nodiscard]] virtual QByteArray exec(const QStringList& args) = 0;

 protected:
  template <typename TYPE>
  [[nodiscard]] QByteArray serialize(const TYPE& data);

 private:
  const ResponseSerializer& m_serializer;
};

template <typename TYPE>
QByteArray Command::serialize(const TYPE& data) {
  return m_serializer.serialize(data);
}

}  // namespace aegis_server

#endif  // AEGIS_SERVER_COMMAND_COMMAND_H