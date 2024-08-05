/* ----------------------------------- Local -------------------------------- */
#include "aegis/search_command/plugin.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

SnifferCommandPlugin::SnifferCommandPlugin() = default;

SnifferCommandPlugin::~SnifferCommandPlugin() = default;

void SnifferCommandPlugin::init() { addObject(new FindCommandFactory(this)); }

}  // namespace aegis