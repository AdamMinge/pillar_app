/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_document_plugin.h"
#include "flow/plugins/document/flow/flow_document_format_flow.h"
#include "flow/plugins/document/flow/flow_editor.h"
#include "flow/plugins/document/flow/flow_script_module.h"
#include "flow/plugins/document/flow/new_flow_document_widget.h"
/* -------------------------------------------------------------------------- */

FlowDocumentPlugin::FlowDocumentPlugin() = default;

FlowDocumentPlugin::~FlowDocumentPlugin() = default;

void FlowDocumentPlugin::init()
{
  addObject(new FlowEditor);
  addObject(new FlowScriptModule);
  addObject(new FlowDocumentFormatFlow);
  addObject(new NewFlowDocumentWidgetFactory);
  addObject(new NewFlowDocumentWidgetFactory);
}
