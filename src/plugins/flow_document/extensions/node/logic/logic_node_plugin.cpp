/* ----------------------------------- Local -------------------------------- */
#include "logic_node_plugin.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------ LogicNodePlugin --------------------------- */

LogicNodePlugin::LogicNodePlugin() = default;

LogicNodePlugin::~LogicNodePlugin() = default;

void LogicNodePlugin::init() {
  addObject(new LogicNodeAndFactory(tr("and"), tr("Logic"), this));
  addObject(new LogicNodeNAndFactory(tr("nand"), tr("Logic"), this));
  addObject(new LogicNodeNotFactory(tr("not"), tr("Logic"), this));
  addObject(new LogicNodeOrFactory(tr("or"), tr("Logic"), this));
  addObject(new LogicNodeXOrFactory(tr("xor"), tr("Logic"), this));
  addObject(
      new LogicNodeBoolEmitterFactory(tr("bool emitter"), tr("Logic"), this));
  addObject(
      new LogicNodeBoolReceiverFactory(tr("bool receiver"), tr("Logic"), this));
}
