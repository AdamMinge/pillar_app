#ifndef AEGIS_SERVER_COMMAND_COMMAND_H
#define AEGIS_SERVER_COMMAND_COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QByteArray>
#include <QCommandLineParser>
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
  explicit Command(const QString& name, const CommandExecutor& manager);
  virtual ~Command();

  [[nodiscard]] QByteArray exec(const QStringList& args);

  [[nodiscard]] QString getName() const;
  [[nodiscard]] QString getError() const;
  [[nodiscard]] QString getHelp() const;

  const CommandExecutor& getExecutor() const;

 protected:
  [[nodiscard]] virtual QByteArray exec() = 0;

 protected:
  QString m_name;
  QCommandLineParser m_parser;
  const CommandExecutor& m_executor;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_COMMAND_COMMAND_H