/* ----------------------------------- Local -------------------------------- */
#include "aegis/recorder_command/plugin.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

RecorderCommandPlugin::RecorderCommandPlugin() = default;

RecorderCommandPlugin::~RecorderCommandPlugin() = default;

void RecorderCommandPlugin::init() {
  addObject(new RecordCommandFactory(this));
}

}  // namespace aegis