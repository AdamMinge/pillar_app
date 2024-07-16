#ifndef CONDITION_NODE_PLUGIN_H
#define CONDITION_NODE_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "flow/condition_node_dispatcher.h"
#include "flow/condition_node_switcher.h"
/* -------------------------------------------------------------------------- */

class CONDITION_NODE_API ConditionNodePlugin : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit ConditionNodePlugin();
  ~ConditionNodePlugin() override;

  void init() override;
};

DECLARE_NODE_FACTORY(CONDITION_NODE_API, ConditionNodeSwitcher)
DECLARE_NODE_FACTORY(CONDITION_NODE_API, ConditionNodeDispatcher)

#endif  // CONDITION_NODE_PLUGIN_H
