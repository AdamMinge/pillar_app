/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/flow_tools_bar.h"
#include "flow/plugins/document/flow/flow_selection_tool.h"
#include "flow/plugins/document/flow/flow_tools_manager.h"
/* -------------------------------------------------------------------------- */

FlowToolsBar::FlowToolsBar(QWidget *parent) : QToolBar(parent)
{
  setObjectName(QLatin1String("FlowToolsBar"));

  auto &tools_manager = FlowToolsManager::getInstance();
  addAction(tools_manager.registerTool(new FlowSelectionTool(this)));
}

FlowToolsBar::~FlowToolsBar() = default;