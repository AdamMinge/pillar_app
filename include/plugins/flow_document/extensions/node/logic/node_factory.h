#ifndef NODE_FACTORY_H
#define NODE_FACTORY_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/node/node_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeFactories : public flow_document::NodeFactories {
  Q_OBJECT
  Q_INTERFACES(flow_document::NodeFactories);
  Q_PLUGIN_METADATA(IID "org.flow.NodeFactories" FILE "plugin.json")

 public:
  explicit LogicNodeFactories();
  ~LogicNodeFactories() override;
};

#endif  // NODE_FACTORY_H
