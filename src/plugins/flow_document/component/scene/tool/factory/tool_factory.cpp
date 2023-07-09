/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/factory/tool_factory.h"

#include "flow_document/component/scene/tool/selection_tool.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------------- ToolFactory ----------------------------- */

ToolFactory::ToolFactory(QObject* parent) : QObject(parent) {}

ToolFactory::~ToolFactory() = default;

/* ---------------------------- SelectionToolFactory ------------------------ */

SelectionToolFactory::SelectionToolFactory(QObject* parent)
    : ToolFactory(parent) {}

SelectionToolFactory::~SelectionToolFactory() = default;

Tool* SelectionToolFactory::create(QObject* parent) const {
  return new SelectionTool(parent);
}

}  // namespace flow_document