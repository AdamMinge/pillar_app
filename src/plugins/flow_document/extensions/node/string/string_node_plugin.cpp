/* ----------------------------------- Local -------------------------------- */
#include "string_node_plugin.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------ StringNodePlugin -------------------------- */

StringNodePlugin::StringNodePlugin() = default;

StringNodePlugin::~StringNodePlugin() = default;

void StringNodePlugin::init() {
  addObject(
      new StringNodeValueEmitterFactory(tr("Emitter"), tr("String"), this));
  addObject(
      new StringNodeValueReceiverFactory(tr("Receiver"), tr("String"), this));
}
