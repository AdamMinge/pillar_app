/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/node_factory.h"
#include "flow/plugins/node/node/logic/logic_node_and.h"
#include "flow/plugins/node/node/logic/logic_node_not.h"
#include "flow/plugins/node/node/logic/logic_node_or.h"
/* -------------------------------------------------------------------------- */

LogicNodeFactories::LogicNodeFactories()
    : flow::node::NodeFactories(tr("Logic"))
{
  registerFactory(
    QLatin1String("LogicNodeNot"),
    std::make_unique<flow::node::BaseNodeFactory<LogicNodeNot>>(tr("Not")));

  registerFactory(
    QLatin1String("LogicNodeAnd"),
    std::make_unique<flow::node::BaseNodeFactory<LogicNodeAnd>>(tr("And")));

  registerFactory(
    QLatin1String("LogicNodeOr"),
    std::make_unique<flow::node::BaseNodeFactory<LogicNodeOr>>(tr("Or")));
}

LogicNodeFactories::~LogicNodeFactories() = default;