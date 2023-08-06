/* ----------------------------------- Local -------------------------------- */
#include "logic_node_plugin.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------ LogicNodePlugin --------------------------- */

LogicNodePlugin::LogicNodePlugin() = default;

LogicNodePlugin::~LogicNodePlugin() = default;

void LogicNodePlugin::init() {
  addObject(new LogicNodeAndFactory(tr("And"), tr("Logic"), this));
  addObject(new LogicNodeNotFactory(tr("Not"), tr("Logic"), this));
  addObject(new LogicNodeOrFactory(tr("Or"), tr("Logic"), this));
  addObject(new LogicNodeValueEmitterFactory(tr("Emitter"), tr("Logic"), this));
  addObject(
      new LogicNodeValueReceiverFactory(tr("Receiver"), tr("Logic"), this));
}
