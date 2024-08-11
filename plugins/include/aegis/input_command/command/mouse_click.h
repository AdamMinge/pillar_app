#ifndef AEGIS_INPUT_COMMAND_MOUSE_CLICK_H
#define AEGIS_INPUT_COMMAND_MOUSE_CLICK_H

/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseClickCommand -------------------------- */

class LIB_AEGIS_INPUT_COMMAND_API MouseClickCommand : public Command {
 public:
  explicit MouseClickCommand(const CommandExecutor& manager);
  ~MouseClickCommand() override;

  [[nodiscard]] QString getName() const override;

 protected:
  [[nodiscard]] QList<QCommandLineOption> getOptions() const override;
  [[nodiscard]] QByteArray exec(const QCommandLineParser& parser) override;
};

}  // namespace aegis

#endif  // AEGIS_INPUT_COMMAND_MOUSE_CLICK_H