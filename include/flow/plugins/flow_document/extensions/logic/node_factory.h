#ifndef PLUGIN_FLOW_NODE_FACTORY_H
#define PLUGIN_FLOW_NODE_FACTORY_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{
  class Node;
}

class LOGIC_NODE_API LogicNodeFactories : public flow::node::NodeFactories
{
  Q_OBJECT
  Q_INTERFACES(flow::node::NodeFactories);
  Q_PLUGIN_METADATA(IID "org.flow.NodeFactories" FILE "plugin.json")

public:
  explicit LogicNodeFactories();
  ~LogicNodeFactories() override;
};

#endif//PLUGIN_FLOW_NODE_FACTORY_H
