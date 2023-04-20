/* ----------------------------------- Local -------------------------------- */
#include "node_factory.h"

#include "logic_node_and.h"
#include "logic_node_not.h"
#include "logic_node_or.h"
/* -------------------------------------------------------------------------- */

LogicNodeFactories::LogicNodeFactories()
    : flow_document::NodeFactories(tr("Logic")) {
  registerFactory(
      std::make_unique<flow_document::BaseNodeFactory<LogicNodeNot>>(
          tr("Not"), QLatin1String("LogicNodeNot")));

  registerFactory(
      std::make_unique<flow_document::BaseNodeFactory<LogicNodeAnd>>(
          tr("And"), QLatin1String("LogicNodeAnd")));

  registerFactory(std::make_unique<flow_document::BaseNodeFactory<LogicNodeOr>>(
      tr("Or"), QLatin1String("LogicNodeOr")));
}

LogicNodeFactories::~LogicNodeFactories() = default;