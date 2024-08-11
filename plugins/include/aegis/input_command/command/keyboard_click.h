#ifndef AEGIS_INPUT_COMMAND_KEYBOARD_CLICK_H
#define AEGIS_INPUT_COMMAND_KEYBOARD_CLICK_H

/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------- KeyboardClickCommand ------------------------ */

class LIB_AEGIS_INPUT_COMMAND_API KeyboardClickCommand : public Command {
 public:
  explicit KeyboardClickCommand(const CommandExecutor& manager);
  ~KeyboardClickCommand() override;

  [[nodiscard]] QString getName() const override;

 protected:
  [[nodiscard]] QList<QCommandLineOption> getOptions() const override;
  [[nodiscard]] QByteArray exec(const QCommandLineParser& parser) override;
};

}  // namespace aegis

#endif  // AEGIS_INPUT_COMMAND_KEYBOARD_CLICK_H