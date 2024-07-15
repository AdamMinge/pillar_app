/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_script_module.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowScriptModule::FlowScriptModule(QObject *parent)
    : egnite::ScriptModule(parent) {}

FlowScriptModule::~FlowScriptModule() = default;

QString FlowScriptModule::getName() const { return QLatin1String("Flow"); }

}  // namespace flow_document