/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/abstract_tool_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

AbstractToolFactory::AbstractToolFactory(QObject* parent) : QObject(parent) {}

AbstractToolFactory::~AbstractToolFactory() = default;

}  // namespace flow_document