#ifndef AEGIS_SERVER_COMMAND_COMMAND_H
#define AEGIS_SERVER_COMMAND_COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QByteArray>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace qtils {
class OArchive;
}

namespace aegis {

class CommandExecutor;

/* ---------------------------------- Command ------------------------------- */

class LIB_AEGIS_SERVER_API Command {
 public:
  explicit Command(const CommandExecutor& manager);
  virtual ~Command();

  [[nodiscard]] virtual QString getName() const = 0;

  [[nodiscard]] virtual QByteArray exec(const QStringList& args) = 0;

 protected:
  const CommandExecutor& getManager() const;

 private:
  const CommandExecutor& m_manager;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_COMMAND_COMMAND_H