/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/node_factory.h"
#include "flow/plugins/node/node/logic/logic_node_and.h"
#include "flow/plugins/node/node/logic/logic_node_not.h"
#include "flow/plugins/node/node/logic/logic_node_or.h"
/* -------------------------------------------------------------------------- */

LogicNodeFactories::LogicNodeFactories()
    : flow::node::NodeFactories(tr("Logic"))
{
  registerFactory(std::make_unique<flow::node::BaseNodeFactory<LogicNodeNot>>(
    tr("Not"), QLatin1String("LogicNodeNot")));

  registerFactory(std::make_unique<flow::node::BaseNodeFactory<LogicNodeAnd>>(
    tr("And"), QLatin1String("LogicNodeAnd")));

  registerFactory(std::make_unique<flow::node::BaseNodeFactory<LogicNodeOr>>(
    tr("Or"), QLatin1String("LogicNodeOr")));
}

LogicNodeFactories::~LogicNodeFactories() = default;