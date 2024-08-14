/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/command/set_property.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ----------------------------- SetPropertyCommand ------------------------- */

SetPropertyCommand::SetPropertyCommand()
    : Command(QLatin1String("SetProperty")) {}

SetPropertyCommand::~SetPropertyCommand() = default;

QByteArray SetPropertyCommand::exec() {
  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serializer()->serialize(error);
}

}  // namespace aegis