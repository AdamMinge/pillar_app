#ifndef AEGIS_SERVER_COMMAND_COMMAND_FACTORY_H
#define AEGIS_SERVER_COMMAND_COMMAND_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class Command;
class ResponseSerializer;

/* ------------------------------- CommandFactory --------------------------- */

class LIB_AEGIS_SERVER_API CommandFactory : public QObject {
  Q_OBJECT

 public:
  explicit CommandFactory(QObject* parent = nullptr);
  ~CommandFactory() override;

  [[nodiscard]] virtual std::unique_ptr<Command> create(
      const ResponseSerializer& serializer) const = 0;
};

}  // namespace aegis

Q_DECLARE_INTERFACE(aegis::CommandFactory, "org.aegis.CommandFactory")

#endif  // AEGIS_SERVER_COMMAND_COMMAND_FACTORY_H