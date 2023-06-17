/* ----------------------------------- Local -------------------------------- */
#include "logic_group_factory.h"

#include "logic_node_and.h"
#include "logic_node_not.h"
#include "logic_node_or.h"
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/factory/node_factory.h>
/* -------------------------------------------------------------------------- */

LogicGroupFactory::LogicGroupFactory()
    : flow_document::GroupFactory(tr("Logic")) {
  auto nodes_group = std::make_unique<flow_document::GroupFactory>(tr("Nodes"));

  nodes_group->append(
      std::make_unique<flow_document::BaseNodeFactory<LogicNodeNot>>(
          tr("Not")));

  nodes_group->append(
      std::make_unique<flow_document::BaseNodeFactory<LogicNodeAnd>>(
          tr("And")));

  nodes_group->append(
      std::make_unique<flow_document::BaseNodeFactory<LogicNodeOr>>(tr("Or")));

  append(std::move(nodes_group));
}

LogicGroupFactory::~LogicGroupFactory() = default;