/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/flow_document/flow_document_plugin.h"

#include "flow/plugins/flow_document/flow_document_format_flow.h"
#include "flow/plugins/flow_document/flow_editor.h"
#include "flow/plugins/flow_document/flow_script_module.h"
#include "flow/plugins/flow_document/new_flow_document_widget.h"
/* -------------------------------------------------------------------------- */

namespace plugin::flow_document {

FlowDocumentPlugin::FlowDocumentPlugin() = default;

FlowDocumentPlugin::~FlowDocumentPlugin() = default;

void FlowDocumentPlugin::init() {
  addObject(new FlowEditor);
  addObject(new FlowScriptModule);
  addObject(new FlowDocumentFormatFlow);
  addObject(new NewFlowDocumentWidgetFactory);
}

}  // namespace plugin::flow_document