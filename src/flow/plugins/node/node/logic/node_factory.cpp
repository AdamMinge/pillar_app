/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/node_factory.h"
#include "flow/plugins/node/node/logic/logic_node_and.h"
#include "flow/plugins/node/node/logic/logic_node_not.h"
#include "flow/plugins/node/node/logic/logic_node_or.h"
/* -------------------------------------------------------------------------- */

LogicNodeFactories::LogicNodeFactories()
    : flow::node::NodeFactories(tr("Logic"), QIcon())
{
  registerFactory(
    QLatin1String("LogicNodeNot"),
    std::make_unique<flow::node::BaseNodeFactory<LogicNodeNot>>(
      tr("Not"),
      QIcon(":/plugins/node/logic/images/32x32/logic_gate_not.png")));

  registerFactory(
    QLatin1String("LogicNodeAnd"),
    std::make_unique<flow::node::BaseNodeFactory<LogicNodeAnd>>(
      tr("And"),
      QIcon(":/plugins/node/logic/images/32x32/logic_gate_and.png")));

  registerFactory(
    QLatin1String("LogicNodeOr"),
    std::make_unique<flow::node::BaseNodeFactory<LogicNodeOr>>(
      tr("Or"), QIcon(":/plugins/node/logic/images/32x32/logic_gate_or.png")));
}

LogicNodeFactories::~LogicNodeFactories() = default;