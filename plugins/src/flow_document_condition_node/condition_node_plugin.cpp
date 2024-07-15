/* ----------------------------------- Local -------------------------------- */
#include "condition_node_plugin.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- ConditionNodePlugin ------------------------ */

ConditionNodePlugin::ConditionNodePlugin() = default;

ConditionNodePlugin::~ConditionNodePlugin() = default;

void ConditionNodePlugin::init() {
  addObject(
      new ConditionNodeSwitcherFactory(tr("switcher"), tr("Condition"), this));
  addObject(new ConditionNodeDispatcherFactory(tr("dispatcher"),
                                               tr("Condition"), this));
}
