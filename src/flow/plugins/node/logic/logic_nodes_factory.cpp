/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/logic_nodes_factory.h"
#include "flow/plugins/node/logic/logic_node_and.h"
#include "flow/plugins/node/logic/logic_node_not.h"
#include "flow/plugins/node/logic/logic_node_or.h"
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  LogicNodesFactory::LogicNodesFactory()
  {
    registerFactory(QLatin1String("LogicNodeNot"), []() {
      return std::make_unique<LogicNodeNot>();
    });
    registerFactory(QLatin1String("LogicNodeOr"), []() {
      return std::make_unique<LogicNodeOr>();
    });
    registerFactory(QLatin1String("LogicNodeAnd"), []() {
      return std::make_unique<LogicNodeAnd>();
    });
  }

  LogicNodesFactory::~LogicNodesFactory() = default;

}// namespace plugins::node::logic
