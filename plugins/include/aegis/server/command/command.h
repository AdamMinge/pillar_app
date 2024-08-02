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

class CommandManager;

/* ---------------------------------- Command ------------------------------- */

class LIB_AEGIS_SERVER_API Command {
 public:
  explicit Command(const CommandManager& manager);
  virtual ~Command();

  [[nodiscard]] virtual QString getName() const = 0;

  [[nodiscard]] virtual QByteArray exec(const QStringList& args) = 0;

 protected:
  const CommandManager& getManager() const;

 private:
  const CommandManager& m_manager;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_COMMAND_COMMAND_H