#ifndef LOGIC_NODE_PLUGIN_H
#define LOGIC_NODE_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/properties/factory/utils.h>
#include <flow_document/component/scene/item/factory/utils.h>
#include <flow_document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "component/properties/logic_node_value_properties.h"
#include "component/scene/item/logic_node_value_item.h"
#include "export.h"
#include "flow/logic_node_and.h"
#include "flow/logic_node_nand.h"
#include "flow/logic_node_not.h"
#include "flow/logic_node_or.h"
#include "flow/logic_node_value.h"
#include "flow/logic_node_xor.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodePlugin : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
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

DECLARE_GRAPHICS_ITEM_FACTORY(LOGIC_NODE_API, LogicNodeBoolReceiverItem,
                              LogicNodeBoolReceiver);
DECLARE_GRAPHICS_ITEM_FACTORY(LOGIC_NODE_API, LogicNodeBoolEmitterItem,
                              LogicNodeBoolEmitter);

DECLARE_OBJECT_PROPERTIES_FACTORY(LOGIC_NODE_API,
                                  LogicNodeBoolEmitterProperties,
                                  LogicNodeBoolEmitter);

#endif  // LOGIC_NODE_PLUGIN_H
