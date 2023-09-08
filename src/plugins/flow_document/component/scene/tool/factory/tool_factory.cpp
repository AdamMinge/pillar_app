/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/factory/tool_factory.h"

#include "flow_document/component/scene/tool/node_connection_tool.h"
#include "flow_document/component/scene/tool/node_selection_tool.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------------- ToolFactory ----------------------------- */

ToolFactory::ToolFactory(QObject* parent) : QObject(parent) {}

ToolFactory::~ToolFactory() = default;

/* -------------------------- NodeSelectionToolFactory ---------------------- */

NodeSelectionToolFactory::NodeSelectionToolFactory(QObject* parent)
    : ToolFactory(parent) {}

NodeSelectionToolFactory::~NodeSelectionToolFactory() = default;

Tool* NodeSelectionToolFactory::create(QObject* parent) const {
  return new NodeSelectionTool(parent);
}

/* -------------------------- NodeConnectionToolFactory --------------------- */

NodeConnectionToolFactory::NodeConnectionToolFactory(QObject* parent)
    : ToolFactory(parent) {}

NodeConnectionToolFactory::~NodeConnectionToolFactory() = default;

Tool* NodeConnectionToolFactory::create(QObject* parent) const {
  return new NodeConnectionTool(parent);
}

}  // namespace flow_document