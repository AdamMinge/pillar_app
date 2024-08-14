#ifndef AEGIS_INPUT_COMMAND_MOUSE_MOVE_H
#define AEGIS_INPUT_COMMAND_MOUSE_MOVE_H

/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/input_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- MouseMoveCommand --------------------------- */

class LIB_AEGIS_INPUT_COMMAND_API MouseMoveCommand : public Command {
 public:
  explicit MouseMoveCommand();
  ~MouseMoveCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;
};

}  // namespace aegis

#endif  // AEGIS_INPUT_COMMAND_MOUSE_MOVE_H