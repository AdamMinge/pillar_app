#ifndef STRING_NODE_PLUGIN_H
#define STRING_NODE_PLUGIN_H

/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "string_node_contains.h"
#include "string_node_count.h"
#include "string_node_equal.h"
#include "string_node_insert.h"
#include "string_node_lower.h"
#include "string_node_mid.h"
#include "string_node_not_equal.h"
#include "string_node_remove.h"
#include "string_node_replace.h"
#include "string_node_reverse.h"
#include "string_node_upper.h"
#include "string_node_value.h"
/* -------------------------------------------------------------------------- */

class STRING_NODE_API StringNodePlugin : public egnite::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(egnite::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit StringNodePlugin();
  ~StringNodePlugin() override;

  void init() override;
};

DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeContains)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeCount)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeEqual)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeInsert)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeLower)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeMid)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeNotEqual)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeRemove)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeReplace)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeReverse)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeUpper)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeStringEmitter)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeStringReceiver)

#endif  // STRING_NODE_PLUGIN_H
