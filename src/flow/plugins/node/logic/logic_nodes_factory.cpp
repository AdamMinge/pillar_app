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
    registerFactory(
      QLatin1String("LogicNodeNot"),
      Factory(
        []() { return std::make_unique<LogicNodeNot>(); },
        QObject::tr("Logic Not"), QIcon()));

    registerFactory(
      QLatin1String("LogicNodeOr"),
      Factory(
        []() { return std::make_unique<LogicNodeOr>(); },
        QObject::tr("Logic Or"), QIcon()));

    registerFactory(
      QLatin1String("LogicNodeAnd"),
      Factory(
        []() { return std::make_unique<LogicNodeAnd>(); },
        QObject::tr("Logic And"), QIcon()));
  }

  LogicNodesFactory::~LogicNodesFactory() = default;

}// namespace plugins::node::logic
