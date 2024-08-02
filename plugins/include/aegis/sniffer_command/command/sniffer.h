#ifndef AEGIS_SNIFFER_COMMAND_SNIFFER_H
#define AEGIS_SNIFFER_COMMAND_SNIFFER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QCommandLineParser>
#include <QObject>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/sniffer_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ------------------------------ SnifferCommand ---------------------------- */

class LIB_AEGIS_SNIFFER_COMMAND_API SnifferCommand : public Command {
 public:
  explicit SnifferCommand(const CommandManager& manager);
  ~SnifferCommand() override;

  [[nodiscard]] QString getName() const override;

  [[nodiscard]] QByteArray exec(const QStringList& args) override;

 private:
  QCommandLineParser m_parser;
};

}  // namespace aegis

#endif  // AEGIS_SNIFFER_COMMAND_SNIFFER_H