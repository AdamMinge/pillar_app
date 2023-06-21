/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/factory/node_factory.h"

#include "flow_document/flow/node.h"
#include "flow_document/resources.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

NodeFactory::NodeFactory(QString name, QString section, QObject* parent)
    : NodeFactory(std::move(name), std::move(section), QIcon(icons::x32::Node),
                  parent) {}

NodeFactory::NodeFactory(QString name, QString section, QIcon icon,
                         QObject* parent)
    : ObjectFactory(Type::NodeFactory, std::move(name), std::move(section),
                    std::move(icon), parent) {}

NodeFactory::~NodeFactory() = default;

}  // namespace flow_document