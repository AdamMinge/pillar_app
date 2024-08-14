#ifndef AEGIS_OBJECT_COMMAND_COMMAND_DUMP_H
#define AEGIS_OBJECT_COMMAND_COMMAND_DUMP_H

/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------------- Dumper -------------------------------- */

class LIB_AEGIS_OBJECT_COMMAND_API Dumper {
 public:
  using Result = Response<>;

 public:
  explicit Dumper();
  ~Dumper();
};

/* -------------------------------- DumpCommand ----------------------------- */

class LIB_AEGIS_OBJECT_COMMAND_API DumpCommand : public Command {
 public:
  explicit DumpCommand();
  ~DumpCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;
};

}  // namespace aegis

#endif  // AEGIS_OBJECT_COMMAND_COMMAND_DUMP_H
