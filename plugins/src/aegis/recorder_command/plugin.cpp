/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/plugin.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

RecorderCommandPlugin::RecorderCommandPlugin() = default;

RecorderCommandPlugin::~RecorderCommandPlugin() = default;

void RecorderCommandPlugin::init() {
  addObject(new RecorderCommandFactory(this));
}

}  // namespace aegis