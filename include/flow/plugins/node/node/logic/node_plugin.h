#ifndef FLOW_NODE_PLUGIN_H
#define FLOW_NODE_PLUGIN_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/plugin_interface.h>
/* -------------------------------------------------------------------------- */

namespace flow::node
{
  class Node;
}

class LOGIC_NODE_API NodePlugin : public flow::PluginInterface
{
  Q_OBJECT
  Q_INTERFACES(flow::PluginInterface);
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

public:
  explicit NodePlugin();
  ~NodePlugin() override;

private:
  QScopedPointer<flow::node::Node> m_not_node;
  QScopedPointer<flow::node::Node> m_and_node;
  QScopedPointer<flow::node::Node> m_or_node;
};

#endif//FLOW_NODE_PLUGIN_H
