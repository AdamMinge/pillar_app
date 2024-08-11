#ifndef AEGIS_SERVER_COMMAND_COMMAND_H
#define AEGIS_SERVER_COMMAND_COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QByteArray>
#include <QCommandLineOption>
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
  explicit Command(const CommandExecutor& manager);
  virtual ~Command();

  [[nodiscard]] QByteArray exec(const QStringList& args);

  [[nodiscard]] virtual QString getName() const = 0;
  [[nodiscard]] virtual QString getError() const;

  const CommandExecutor& getExecutor() const;

 protected:
  [[nodiscard]] virtual QList<QCommandLineOption> getOptions() const = 0;
  [[nodiscard]] virtual QByteArray exec(const QCommandLineParser& parser) = 0;

  [[nodiscard]] QString getHelp(const QCommandLineParser& parser) const;

 private:
  const CommandExecutor& m_executor;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_COMMAND_COMMAND_H