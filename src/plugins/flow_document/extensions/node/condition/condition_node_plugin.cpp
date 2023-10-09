/* ----------------------------------- Local -------------------------------- */
#include "condition_node_plugin.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- ConditionNodePlugin ------------------------ */

ConditionNodePlugin::ConditionNodePlugin() = default;

ConditionNodePlugin::~ConditionNodePlugin() = default;

void ConditionNodePlugin::init() {
  addObject(new ConditionNodeIfFactory(tr("If"), tr("Condition"), this));
}
