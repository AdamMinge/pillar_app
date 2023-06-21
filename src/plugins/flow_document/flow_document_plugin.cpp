/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_plugin.h"

#include "flow_document/component/flow_dock_widget_factory.h"
#include "flow_document/component/properties/object_properties_factory.h"
#include "flow_document/component/scene/item/factory/graphics_item_factory.h"
#include "flow_document/component/scene/tool/factory/abstract_tool_factory.h"
#include "flow_document/flow/factory/layer_factory.h"
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

  addObject(new FactoriesDockWidgetFactory(this));
  addObject(new LayersDockWidgetFactory(this));
  addObject(new NodesDockWidgetFactory(this));
  addObject(new PropertiesDockWidgetFactory(this));

  addObject(new GroupLayerItemFactory(this));
  addObject(new NodeLayerItemFactory(this));
  addObject(new NodeItemFactory(this));

  addObject(new SelectionToolFactory(this));

  addObject(new LayerPropertiesFactory(this));
  addObject(new NodePropertiesFactory(this));

  addObject(new GroupLayerFactory(this));
  addObject(new NodeLayerFactory(this));

  addObject(
      new egnite::BaseLanguageTranslator(translations::TranslationsPath, this));
}

}  // namespace flow_document