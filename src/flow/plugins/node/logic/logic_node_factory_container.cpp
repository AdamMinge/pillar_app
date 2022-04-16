/* ------------------------------------ Node -------------------------------- */
#include <flow/modules/node/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/logic_node_and.h"
#include "flow/plugins/node/logic/logic_node_factory_container.h"
#include "flow/plugins/node/logic/logic_node_not.h"
#include "flow/plugins/node/logic/logic_node_or.h"
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  LogicNodeFactoryContainer::LogicNodeFactoryContainer()
  {
    addFactory(std::make_unique<::node::NodeFactory>(
      []() { return std::make_unique<LogicNodeNot>(); },
      QObject::tr("Logic Not"), QIcon()));

    addFactory(std::make_unique<::node::NodeFactory>(
      []() { return std::make_unique<LogicNodeOr>(); }, QObject::tr("Logic Or"),
      QIcon()));

    addFactory(std::make_unique<::node::NodeFactory>(
      []() { return std::make_unique<LogicNodeAnd>(); },
      QObject::tr("Logic And"), QIcon()));
  }

  LogicNodeFactoryContainer::~LogicNodeFactoryContainer() = default;

  QString LogicNodeFactoryContainer::getName() const
  {
    return QObject::tr("Logic Nodes");
  }

}// namespace plugins::node::logic
