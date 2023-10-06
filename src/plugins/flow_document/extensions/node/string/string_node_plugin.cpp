/* ----------------------------------- Local -------------------------------- */
#include "string_node_plugin.h"
/* -------------------------------------------------------------------------- */

/* ------------------------------ StringNodePlugin -------------------------- */

StringNodePlugin::StringNodePlugin() = default;

StringNodePlugin::~StringNodePlugin() = default;

void StringNodePlugin::init() {
  addObject(new StringNodeContainsFactory(tr("Contains"), tr("String"), this));
  addObject(new StringNodeCountFactory(tr("Count"), tr("String"), this));
  addObject(new StringNodeEqualFactory(tr("Equal"), tr("String"), this));
  addObject(new StringNodeInsertFactory(tr("Insert"), tr("String"), this));
  addObject(new StringNodeLowerFactory(tr("Lower"), tr("String"), this));
  addObject(new StringNodeMidFactory(tr("Mid"), tr("String"), this));
  addObject(new StringNodeNotEqualFactory(tr("Not Equal"), tr("String"), this));
  addObject(new StringNodeRemoveFactory(tr("Remove"), tr("String"), this));
  addObject(new StringNodeReplaceFactory(tr("Replace"), tr("String"), this));
  addObject(new StringNodeReverseFactory(tr("Reverse"), tr("String"), this));
  addObject(new StringNodeUpperFactory(tr("Upper"), tr("String"), this));
  addObject(new StringNodeStringEmitterFactory(tr("String Emitter"),
                                               tr("String"), this));
  addObject(new StringNodeStringReceiverFactory(tr("String Receiver"),
                                                tr("String"), this));
}
