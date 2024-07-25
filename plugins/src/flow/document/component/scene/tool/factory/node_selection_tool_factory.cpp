/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/tool/factory/node_selection_tool_factory.h"

#include "flow/document/component/scene/tool/node_selection_tool.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* -------------------------- NodeSelectionToolFactory ---------------------- */

NodeSelectionToolFactory::NodeSelectionToolFactory(QObject* parent)
    : ToolFactory(parent) {}

NodeSelectionToolFactory::~NodeSelectionToolFactory() = default;

Tool* NodeSelectionToolFactory::create(QObject* parent) const {
  return new NodeSelectionTool(parent);
}

}  // namespace flow