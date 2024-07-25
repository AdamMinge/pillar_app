#ifndef AEGIS_USER_INPUT_COMMAND_MOUSE_MOVE_H
#define AEGIS_USER_INPUT_COMMAND_MOUSE_MOVE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QCommandLineParser>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/user_input_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseMoveCommand --------------------------- */

class LIB_AEGIS_USER_INPUT_COMMAND_API MouseMoveCommand : public Command {
 public:
  explicit MouseMoveCommand(const ResponseSerializer &serializer);
  ~MouseMoveCommand() override;

  [[nodiscard]] QString getName() const override;

  [[nodiscard]] QByteArray exec(const QStringList &args) override;

 private:
  QCommandLineParser m_parser;
};

}  // namespace aegis

#endif  // AEGIS_USER_INPUT_COMMAND_MOUSE_MOVE_H