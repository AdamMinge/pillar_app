#ifndef MATH_NODE_PLUGIN_H
#define MATH_NODE_PLUGIN_H

/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_interface.h>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/factory/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
#include "math_node_value.h"
/* -------------------------------------------------------------------------- */

class MATH_NODE_API MathNodePlugin : public egnite::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(egnite::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit MathNodePlugin();
  ~MathNodePlugin() override;

  void init() override;
};

DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeValueEmitter)
DECLARE_NODE_FACTORY(MATH_NODE_API, MathNodeValueReceiver)

#endif  // MATH_NODE_PLUGIN_H
