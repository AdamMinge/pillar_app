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

/* --------------------------------- HelpGetter ----------------------------- */

class LIB_AEGIS_SERVER_API HelpGetter {
 public:
  explicit HelpGetter();
  ~HelpGetter();

  Response<CommandsHelpMessage> helps();
  Response<CommandsListMessage> commands();
};

/* ------------------------------- HelpCommand ------------------------------ */

class LIB_AEGIS_SERVER_API HelpCommand : public Command {
 public:
  explicit HelpCommand();
  ~HelpCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  HelpGetter m_help_getter;
};

}  // namespace aegis

#endif  // AEGIS_SEARCH_COMMAND_PARENT_H