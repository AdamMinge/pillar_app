#ifndef FLOW_LOGIC_NODE_FACTORY_CONTAINER_H
#define FLOW_LOGIC_NODE_FACTORY_CONTAINER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/export.h"
/* ------------------------------------ Node -------------------------------- */
#include <flow/modules/node/node_factory_container.h>
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  class LOGIC_NODE_API LogicNodeFactoryContainer
      : public QObject,
        public ::node::NodeFactoryContainer
  {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.flow.NodeFactoryContainer" FILE "plugin.json")

  public:
    explicit LogicNodeFactoryContainer();
    ~LogicNodeFactoryContainer() override;

    [[nodiscard]] QString getName() const override;
  };

}// namespace plugins::node::logic

#endif//FLOW_LOGIC_NODE_FACTORY_CONTAINER_H
