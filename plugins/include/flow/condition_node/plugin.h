#ifndef FLOW_CONDITION_NODE_PLUGIN_H
#define FLOW_CONDITION_NODE_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/condition_node/export.h"
#include "flow/condition_node/flow/dispatcher.h"
#include "flow/condition_node/flow/switcher.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_CONDITION_NODE_API ConditionNodePlugin
    : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.pillar.PluginInterface" FILE "plugin.json")

 public:
  explicit ConditionNodePlugin();
  ~ConditionNodePlugin() override;

  void init() override;
};

DECLARE_NODE_FACTORY(LIB_FLOW_CONDITION_NODE_API, ConditionNodeSwitcher)
DECLARE_NODE_FACTORY(LIB_FLOW_CONDITION_NODE_API, ConditionNodeDispatcher)

}  // namespace flow

#endif  // FLOW_CONDITION_NODE_PLUGIN_H
