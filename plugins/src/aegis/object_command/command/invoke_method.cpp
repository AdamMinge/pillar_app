/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/command/invoke_method.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------- InvokeMethodCommand ------------------------- */

InvokeMethodCommand::InvokeMethodCommand()
    : Command(QLatin1String("InvokeMethod")) {}

InvokeMethodCommand::~InvokeMethodCommand() = default;

QByteArray InvokeMethodCommand::exec() {
  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serializer()->serialize(error);
}

}  // namespace aegis