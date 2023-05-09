/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/node_factory.h"

#include "flow_document/flow/node.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

NodeFactory::NodeFactory(QString name, QString id)
    : Factory(Type::NodeFactory, std::move(name)), m_id(std::move(id)) {}

NodeFactory::~NodeFactory() = default;

}  // namespace flow_document