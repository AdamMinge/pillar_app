#ifndef CONDITION_NODE_PLUGIN_H
#define CONDITION_NODE_PLUGIN_H

/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "condition_node_dispatcher.h"
#include "condition_node_switcher.h"
#include "export.h"
/* -------------------------------------------------------------------------- */

class CONDITION_NODE_API ConditionNodePlugin : public egnite::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(egnite::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit ConditionNodePlugin();
  ~ConditionNodePlugin() override;

  void init() override;
};

DECLARE_NODE_FACTORY(CONDITION_NODE_API, ConditionNodeSwitcher)
DECLARE_NODE_FACTORY(CONDITION_NODE_API, ConditionNodeDispatcher)

#endif  // CONDITION_NODE_PLUGIN_H
