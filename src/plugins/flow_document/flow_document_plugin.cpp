/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_plugin.h"

#include "flow_document/flow_document_format_flow.h"
#include "flow_document/flow_editor.h"
#include "flow_document/flow_script_module.h"
#include "flow_document/new_flow_document_widget.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <egnite/language_translator.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowDocumentPlugin::FlowDocumentPlugin() = default;

FlowDocumentPlugin::~FlowDocumentPlugin() = default;

void FlowDocumentPlugin::init() {
  addObject(new FlowEditor(this));
  addObject(new FlowScriptModule(this));
  addObject(new FlowDocumentFormatFlow(this));
  addObject(new NewFlowDocumentWidgetFactory(this));

  addObject(
      new egnite::BaseLanguageTranslator(translations::TranslationsPath, this));
}

}  // namespace flow_document