/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/command/dump.h"
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/plugin_manager.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* ---------------------------------- Dumper -------------------------------- */

Dumper::Dumper() = default;

Dumper::~Dumper() = default;

/* -------------------------------- DumpCommand ----------------------------- */

DumpCommand::DumpCommand() : Command(QLatin1String("Dump")) {
  m_parser.addOptions({{{"q", "query"},
                        "Query that identifies the objects we are dumping for",
                        "query"},
                       {{"p", "properties"}, "Dump properties"},
                       {{"m", "methods"}, "Dump methods"}});
}

DumpCommand::~DumpCommand() = default;

QByteArray DumpCommand::exec() {
  auto error = Response<>(
      ErrorMessage(getError(), "At least one of options must be provided."));
  return serializer()->serialize(error);
}

}  // namespace aegis