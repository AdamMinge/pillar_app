/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/factory/node_factory.h"

#include "flow_document/flow/node.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

NodeFactory::NodeFactory(QString name)
    : Factory(Type::NodeFactory, std::move(name)) {}

NodeFactory::~NodeFactory() = default;

}  // namespace flow_document