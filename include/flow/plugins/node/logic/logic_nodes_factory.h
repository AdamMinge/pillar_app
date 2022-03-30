#ifndef FLOW_LOGIC_NODES_FACTORY_H
#define FLOW_LOGIC_NODES_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/export.h"
/* ------------------------------------ Node -------------------------------- */
#include <flow/modules/node/nodes_factory.h>
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  class LOGIC_NODE_API LogicNodesFactory : public QObject,
                                           public ::node::NodesFactory
  {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.flow.NodesFactory" FILE "plugin.json")

  public:
    explicit LogicNodesFactory();
    ~LogicNodesFactory() override;
  };

}// namespace plugins::node::logic

#endif//FLOW_LOGIC_NODES_FACTORY_H
