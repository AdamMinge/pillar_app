/* ------------------------------------ Node -------------------------------- */
#include <flow/modules/node/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/logic_node_and.h"
#include "flow/plugins/node/node/logic/logic_node_factory_container.h"
#include "flow/plugins/node/node/logic/logic_node_not.h"
#include "flow/plugins/node/node/logic/logic_node_or.h"
/* -------------------------------------------------------------------------- */

LogicNodeFactoryContainer::LogicNodeFactoryContainer()
{
  addFactory(std::make_unique<node::NodeFactory>(
    QLatin1String("LogicNot"),
    []() { return std::make_unique<LogicNodeNot>(); }, QObject::tr("Not"),
    QIcon(":/plugins/logic_node/images/32x32/logic_gate_not.png")));

  addFactory(std::make_unique<node::NodeFactory>(
    QLatin1String("LogicOr"), []() { return std::make_unique<LogicNodeOr>(); },
    QObject::tr("Or"),
    QIcon(":/plugins/logic_node/images/32x32/logic_gate_or.png")));

  addFactory(std::make_unique<node::NodeFactory>(
    QLatin1String("LogicAnd"),
    []() { return std::make_unique<LogicNodeAnd>(); }, QObject::tr("And"),
    QIcon(":/plugins/logic_node/images/32x32/logic_gate_and.png")));
}

LogicNodeFactoryContainer::~LogicNodeFactoryContainer() = default;

QString LogicNodeFactoryContainer::getName() const
{
  return QObject::tr("Logic");
}

QIcon LogicNodeFactoryContainer::getIcon() const
{
  return QIcon(":/plugins/logic_node/images/32x32/logic_nodes.png");
}
