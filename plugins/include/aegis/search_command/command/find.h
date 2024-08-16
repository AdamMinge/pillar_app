#ifndef AEGIS_SEARCH_COMMAND_FIND_H
#define AEGIS_SEARCH_COMMAND_FIND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QTimer>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/search_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------- FoundObjectsMessage ------------------------- */

struct LIB_AEGIS_SEARCH_COMMAND_API FoundObjectsMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QStringList objects MEMBER objects)

  QStringList objects;
};

/* ------------------------------- FindCommand ------------------------------ */

class LIB_AEGIS_SEARCH_COMMAND_API FindCommand : public Command {
 public:
  explicit FindCommand();
  ~FindCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  [[nodiscard]] Response<FoundObjectsMessage> find(const QString& id);
};

}  // namespace aegis

#endif  // AEGIS_SEARCH_COMMAND_FIND_H