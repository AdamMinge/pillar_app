/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/plugin.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

ObjectCommandPlugin::ObjectCommandPlugin() = default;

ObjectCommandPlugin::~ObjectCommandPlugin() = default;

void ObjectCommandPlugin::init() {
  addObject(new InvokeMethodCommandFactory(this));
  addObject(new SetPropertyCommandFactory(this));
  addObject(new DumpPropertiesCommandFactory(this));
  addObject(new DumpMethodsCommandFactory(this));
}

}  // namespace aegis