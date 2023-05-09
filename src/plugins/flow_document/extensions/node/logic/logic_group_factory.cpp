/* ----------------------------------- Local -------------------------------- */
#include "logic_group_factory.h"

#include "logic_node_and.h"
#include "logic_node_not.h"
#include "logic_node_or.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/node_factory.h>
/* -------------------------------------------------------------------------- */

LogicGroupFactory::LogicGroupFactory()
    : flow_document::GroupFactory(tr("Logic")) {
  append(std::make_unique<flow_document::BaseNodeFactory<LogicNodeNot>>(
      tr("Not"), QLatin1String("LogicNodeNot")));

  append(std::make_unique<flow_document::BaseNodeFactory<LogicNodeAnd>>(
      tr("And"), QLatin1String("LogicNodeAnd")));

  append(std::make_unique<flow_document::BaseNodeFactory<LogicNodeOr>>(
      tr("Or"), QLatin1String("LogicNodeOr")));
}

LogicGroupFactory::~LogicGroupFactory() = default;