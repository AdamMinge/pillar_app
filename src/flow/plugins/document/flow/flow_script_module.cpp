/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_script_module.h"
/* -------------------------------------------------------------------------- */

FlowScriptModule::FlowScriptModule(QObject *parent) : flow::ScriptModule(parent)
{}

FlowScriptModule::~FlowScriptModule() = default;

QString FlowScriptModule::getName() const { return QLatin1String("Flow"); }