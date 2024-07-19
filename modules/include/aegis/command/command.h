#ifndef AEGIS_COMMAND_COMMAND_H
#define AEGIS_COMMAND_COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QByteArray>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/export.h"
#include "aegis/serializer.h"
/* -------------------------------------------------------------------------- */

namespace qtils {
class OArchive;
}

namespace aegis {

/* ---------------------------------- Command ------------------------------- */

class LIB_AEGIS_API Command {
 public:
  explicit Command(const Serializer& serializer);
  virtual ~Command();

  [[nodiscard]] virtual QByteArray exec(const QStringList& args) = 0;

 protected:
  template <typename TYPE>
  [[nodiscard]] QByteArray serialize(const TYPE& data);

 private:
  const Serializer& m_serializer;
};

template <typename TYPE>
QByteArray Command::serialize(const TYPE& data) {
  return m_serializer.serialize(data);
}

}  // namespace aegis

#endif  // AEGIS_COMMAND_COMMAND_H