/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/plugin.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* ------------------------------ StringNodePlugin -------------------------- */

StringNodePlugin::StringNodePlugin() = default;

StringNodePlugin::~StringNodePlugin() = default;

void StringNodePlugin::init() {
  addObject(new StringNodeContainsFactory(tr("contains"), tr("String"), this));
  addObject(new StringNodeCountFactory(tr("count"), tr("String"), this));
  addObject(new StringNodeEqualFactory(tr("equal"), tr("String"), this));
  addObject(new StringNodeInsertFactory(tr("insert"), tr("String"), this));
  addObject(new StringNodeLowerFactory(tr("lower"), tr("String"), this));
  addObject(new StringNodeMidFactory(tr("mid"), tr("String"), this));
  addObject(new StringNodeNotEqualFactory(tr("not equal"), tr("String"), this));
  addObject(new StringNodeRemoveFactory(tr("remove"), tr("String"), this));
  addObject(new StringNodeReplaceFactory(tr("replace"), tr("String"), this));
  addObject(new StringNodeReverseFactory(tr("reverse"), tr("String"), this));
  addObject(new StringNodeUpperFactory(tr("upper"), tr("String"), this));
  addObject(new StringNodeStringEmitterFactory(tr("String emitter"),
                                               tr("String"), this));
  addObject(new StringNodeStringReceiverFactory(tr("String receiver"),
                                                tr("String"), this));

  addObject(new StringNodeStringEmitterItemFactory(this));
  addObject(new StringNodeStringReceiverItemFactory(this));

  addObject(new StringNodeStringEmitterPropertiesFactory(this));
}

}  // namespace flow