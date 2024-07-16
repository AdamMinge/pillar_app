/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow_document_plugin.h"

#include "flow_document/component/flow_dock_widget_factory.h"
#include "flow_document/component/properties/factory/connection_properties_factory.h"
#include "flow_document/component/properties/factory/layer_properties_factory.h"
#include "flow_document/component/properties/factory/node_properties_factory.h"
#include "flow_document/component/scene/item/factory/connection_item_factory.h"
#include "flow_document/component/scene/item/factory/flow_item_factory.h"
#include "flow_document/component/scene/item/factory/layer_item_factory.h"
#include "flow_document/component/scene/item/factory/node_item_factory.h"
#include "flow_document/component/scene/tool/factory/node_connection_tool_factory.h"
#include "flow_document/component/scene/tool/factory/node_selection_tool_factory.h"
#include "flow_document/flow/factory/layer_factory.h"
#include "flow_document/flow_document_format_flow.h"
#include "flow_document/flow_editor.h"
#include "flow_document/flow_script_module.h"
#include "flow_document/new_flow_document_widget.h"
#include "flow_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <pillar/language_translator.h>
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
  addObject(new ConnectionsDockWidgetFactory(this));

  addObject(new FlowItemFactory(this));
  addObject(new GroupLayerItemFactory(this));
  addObject(new NodeLayerItemFactory(this));
  addObject(new NodeItemFactory(this));
  addObject(new ConnectionItemFactory(this));

  addObject(new NodeSelectionToolFactory(this));
  addObject(new NodeConnectionToolFactory(this));

  addObject(new LayerPropertiesFactory(this));
  addObject(new NodePropertiesFactory(this));
  addObject(new ConnectionPropertiesFactory(this));

  addObject(new GroupLayerFactory(this));
  addObject(new NodeLayerFactory(this));

  addObject(
      new pillar::BaseLanguageTranslator(translations::TranslationsPath, this));
}

}  // namespace flow_document