/* ----------------------------------- Local -------------------------------- */
#include "aegis/sniffer_command/plugin.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

SnifferCommandPlugin::SnifferCommandPlugin() = default;

SnifferCommandPlugin::~SnifferCommandPlugin() = default;

void SnifferCommandPlugin::init() {
  addObject(new SnifferCommandFactory(this));
}

}  // namespace aegis