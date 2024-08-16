#ifndef AEGIS_SEARCH_COMMAND_PARENT_H
#define AEGIS_SEARCH_COMMAND_PARENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QTimer>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/command.h"
#include "aegis/server/export.h"
#include "aegis/server/response.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- CommandsHelpMessage ------------------------ */

struct LIB_AEGIS_SERVER_API CommandsHelpMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QMap<QString, QString> helps MEMBER helps)

  QMap<QString, QString> helps;
};

/* ----------------------------- CommandsListMessage ------------------------ */

struct LIB_AEGIS_SERVER_API CommandsListMessage {
  Q_GADGET

 public:
  Q_PROPERTY(QStringList commands MEMBER commands)

  QStringList commands;
};

/* ------------------------------- HelpCommand ------------------------------ */

class LIB_AEGIS_SERVER_API HelpCommand : public Command {
 public:
  explicit HelpCommand();
  ~HelpCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  [[nodiscard]] Response<CommandsHelpMessage> helps();
  [[nodiscard]] Response<CommandsListMessage> commands();
};

}  // namespace aegis

#endif  // AEGIS_SEARCH_COMMAND_PARENT_H