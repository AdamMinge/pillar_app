/* ----------------------------------- Local -------------------------------- */
#include "flow/document/script_module.h"
/* -------------------------------------------------------------------------- */

namespace flow {

FlowScriptModule::FlowScriptModule(QObject *parent)
    : pillar::ScriptModule(parent) {}

FlowScriptModule::~FlowScriptModule() = default;

QString FlowScriptModule::getName() const { return QLatin1String("Flow"); }

}  // namespace flow