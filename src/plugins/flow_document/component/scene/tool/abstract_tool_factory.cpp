/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/abstract_tool_factory.h"

#include "flow_document/component/scene/tool/selection_tool.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* ---------------------------- AbstractToolFactory ------------------------- */

AbstractToolFactory::AbstractToolFactory(QObject* parent) : QObject(parent) {}

AbstractToolFactory::~AbstractToolFactory() = default;

/* ---------------------------- SelectionToolFactory ------------------------ */

SelectionToolFactory::SelectionToolFactory(QObject* parent)
    : AbstractToolFactory(parent) {}

SelectionToolFactory::~SelectionToolFactory() = default;

AbstractTool* SelectionToolFactory::create(QObject* parent) const {
  return new SelectionTool(parent);
}

}  // namespace flow_document