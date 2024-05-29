/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/factory/node_connection_tool_factory.h"

#include "flow_document/component/scene/tool/node_connection_tool.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------- NodeConnectionToolFactory --------------------- */

NodeConnectionToolFactory::NodeConnectionToolFactory(QObject* parent)
    : ToolFactory(parent) {}

NodeConnectionToolFactory::~NodeConnectionToolFactory() = default;

Tool* NodeConnectionToolFactory::create(QObject* parent) const {
  return new NodeConnectionTool(parent);
}

}  // namespace flow_document