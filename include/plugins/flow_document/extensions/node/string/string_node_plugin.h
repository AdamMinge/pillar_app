#ifndef STRING_NODE_PLUGIN_H
#define STRING_NODE_PLUGIN_H

/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
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

DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeStringEmitter)
DECLARE_NODE_FACTORY(STRING_NODE_API, StringNodeStringReceiver)

#endif  // STRING_NODE_PLUGIN_H
