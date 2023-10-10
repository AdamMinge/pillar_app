#ifndef LOGIC_NODE_PLUGIN_H
#define LOGIC_NODE_PLUGIN_H

/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "logic_node_and.h"
#include "logic_node_nand.h"
#include "logic_node_not.h"
#include "logic_node_or.h"
#include "logic_node_value.h"
#include "logic_node_xor.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodePlugin : public egnite::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(egnite::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit LogicNodePlugin();
  ~LogicNodePlugin() override;

  void init() override;
};

DECLARE_NODE_FACTORY(LOGIC_NODE_API, LogicNodeAnd)
DECLARE_NODE_FACTORY(LOGIC_NODE_API, LogicNodeNAnd)
DECLARE_NODE_FACTORY(LOGIC_NODE_API, LogicNodeNot)
DECLARE_NODE_FACTORY(LOGIC_NODE_API, LogicNodeOr)
DECLARE_NODE_FACTORY(LOGIC_NODE_API, LogicNodeXOr)
DECLARE_NODE_FACTORY(LOGIC_NODE_API, LogicNodeBoolEmitter)
DECLARE_NODE_FACTORY(LOGIC_NODE_API, LogicNodeBoolReceiver)

#endif  // LOGIC_NODE_PLUGIN_H
