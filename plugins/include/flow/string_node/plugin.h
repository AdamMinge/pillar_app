#ifndef STRING_NODE_PLUGIN_H
#define STRING_NODE_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/component/properties/factory/utils.h>
#include <flow/document/component/scene/item/factory/utils.h>
#include <flow/document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/component/properties/node_value_properties.h"
#include "flow/string_node/component/scene/item/node_value_item.h"
#include "flow/string_node/export.h"
#include "flow/string_node/flow/contains.h"
#include "flow/string_node/flow/count.h"
#include "flow/string_node/flow/equal.h"
#include "flow/string_node/flow/insert.h"
#include "flow/string_node/flow/lower.h"
#include "flow/string_node/flow/mid.h"
#include "flow/string_node/flow/not_equal.h"
#include "flow/string_node/flow/remove.h"
#include "flow/string_node/flow/replace.h"
#include "flow/string_node/flow/reverse.h"
#include "flow/string_node/flow/upper.h"
#include "flow/string_node/flow/value.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_STRING_NODE_API StringNodePlugin
    : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit StringNodePlugin();
  ~StringNodePlugin() override;

  void init() override;
};

DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeContains)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeCount)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeEqual)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeInsert)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeLower)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeMid)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeNotEqual)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeRemove)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeReplace)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeReverse)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeUpper)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeStringEmitter)
DECLARE_NODE_FACTORY(LIB_FLOW_STRING_NODE_API, StringNodeStringReceiver)

DECLARE_GRAPHICS_ITEM_FACTORY(LIB_FLOW_STRING_NODE_API,
                              StringNodeStringEmitterItem,
                              StringNodeStringEmitter);
DECLARE_GRAPHICS_ITEM_FACTORY(LIB_FLOW_STRING_NODE_API,
                              StringNodeStringReceiverItem,
                              StringNodeStringReceiver);

DECLARE_OBJECT_PROPERTIES_FACTORY(LIB_FLOW_STRING_NODE_API,
                                  StringNodeStringEmitterProperties,
                                  StringNodeStringEmitter);

}  // namespace flow

#endif  // STRING_NODE_PLUGIN_H
