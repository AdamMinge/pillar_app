/* ----------------------------------- Local -------------------------------- */
#include "math_node_plugin.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------ MathNodePlugin ---------------------------- */

MathNodePlugin::MathNodePlugin() = default;

MathNodePlugin::~MathNodePlugin() = default;

void MathNodePlugin::init() {
  addObject(new MathNodeValueEmitterFactory(tr("Emitter"), tr("Math"), this));
  addObject(new MathNodeValueReceiverFactory(tr("Receiver"), tr("Math"), this));
}
