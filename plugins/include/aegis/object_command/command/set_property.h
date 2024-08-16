#ifndef AEGIS_OBJECT_COMMAND_COMMAND_SET_PROPERTY_H
#define AEGIS_OBJECT_COMMAND_COMMAND_SET_PROPERTY_H

/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/command.h>
#include <aegis/server/response.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- SetPropertyCommand ------------------------- */

class LIB_AEGIS_OBJECT_COMMAND_API SetPropertyCommand : public Command {
 public:
  explicit SetPropertyCommand();
  ~SetPropertyCommand() override;

 protected:
  [[nodiscard]] QByteArray exec() override;

 private:
  [[nodiscard]] Response<> setProperty(const QString& id, const QString& name,
                                       const QString& value);
};

}  // namespace aegis

#endif  // AEGIS_OBJECT_COMMAND_COMMAND_SET_PROPERTY_H
