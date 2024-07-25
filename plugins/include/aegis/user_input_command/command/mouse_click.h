#ifndef AEGIS_USER_INPUT_COMMAND_MOUSE_CLICK_H
#define AEGIS_USER_INPUT_COMMAND_MOUSE_CLICK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QCommandLineParser>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/user_input_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseClickCommand -------------------------- */

class LIB_AEGIS_USER_INPUT_COMMAND_API MouseClickCommand : public Command {
 public:
  explicit MouseClickCommand(const ResponseSerializer &serializer);
  ~MouseClickCommand() override;

  [[nodiscard]] QString getName() const override;

  [[nodiscard]] QByteArray exec(const QStringList &args) override;

 private:
  QCommandLineParser m_parser;
};

}  // namespace aegis

#endif  // AEGIS_USER_INPUT_COMMAND_MOUSE_CLICK_H