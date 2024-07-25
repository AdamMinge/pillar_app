#ifndef LOGIC_NODE_PLUGIN_H
#define LOGIC_NODE_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ---------------------------- Plugin Flow Document ------------------------ */
#include <flow/document/component/properties/factory/utils.h>
#include <flow/document/component/scene/item/factory/utils.h>
#include <flow/document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/logic_node/component/properties/node_value_properties.h"
#include "flow/logic_node/component/scene/item/node_value_item.h"
#include "flow/logic_node/export.h"
#include "flow/logic_node/flow/and.h"
#include "flow/logic_node/flow/nand.h"
#include "flow/logic_node/flow/not.h"
#include "flow/logic_node/flow/or.h"
#include "flow/logic_node/flow/value.h"
#include "flow/logic_node/flow/xor.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_LOGIC_NODE_API LogicNodePlugin : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit LogicNodePlugin();
  ~LogicNodePlugin() override;

  void init() override;
};

DECLARE_NODE_FACTORY(LIB_FLOW_LOGIC_NODE_API, LogicNodeAnd)
DECLARE_NODE_FACTORY(LIB_FLOW_LOGIC_NODE_API, LogicNodeNAnd)
DECLARE_NODE_FACTORY(LIB_FLOW_LOGIC_NODE_API, LogicNodeNot)
DECLARE_NODE_FACTORY(LIB_FLOW_LOGIC_NODE_API, LogicNodeOr)
DECLARE_NODE_FACTORY(LIB_FLOW_LOGIC_NODE_API, LogicNodeXOr)
DECLARE_NODE_FACTORY(LIB_FLOW_LOGIC_NODE_API, LogicNodeBoolEmitter)
DECLARE_NODE_FACTORY(LIB_FLOW_LOGIC_NODE_API, LogicNodeBoolReceiver)

DECLARE_GRAPHICS_ITEM_FACTORY(LIB_FLOW_LOGIC_NODE_API,
                              LogicNodeBoolReceiverItem, LogicNodeBoolReceiver);
DECLARE_GRAPHICS_ITEM_FACTORY(LIB_FLOW_LOGIC_NODE_API, LogicNodeBoolEmitterItem,
                              LogicNodeBoolEmitter);

DECLARE_OBJECT_PROPERTIES_FACTORY(LIB_FLOW_LOGIC_NODE_API,
                                  LogicNodeBoolEmitterProperties,
                                  LogicNodeBoolEmitter);

}  // namespace flow

#endif  // LOGIC_NODE_PLUGIN_H
