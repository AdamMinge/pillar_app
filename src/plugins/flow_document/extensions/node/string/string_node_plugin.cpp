/* ----------------------------------- Local -------------------------------- */
#include "string_node_plugin.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------ StringNodePlugin -------------------------- */

StringNodePlugin::StringNodePlugin() = default;

StringNodePlugin::~StringNodePlugin() = default;

void StringNodePlugin::init() {
  addObject(new StringNodeStringEmitterFactory(tr("String Emitter"),
                                               tr("String"), this));
  addObject(new StringNodeStringReceiverFactory(tr("String Receiver"),
                                                tr("String"), this));
}
