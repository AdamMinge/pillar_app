#ifndef FLOW_LOGIC_NODE_FACTORY_CONTAINER_H
#define FLOW_LOGIC_NODE_FACTORY_CONTAINER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/export.h"
/* ------------------------------------ Node -------------------------------- */
#include <flow/modules/node/node_factory_container.h>
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicNodeFactoryContainer
    : public ::node::NodeFactoryContainer
{
  Q_OBJECT
  Q_INTERFACES(node::NodeFactoryContainer);
  Q_PLUGIN_METADATA(IID "org.flow.NodeFactoryContainer" FILE "plugin.json")

public:
  explicit LogicNodeFactoryContainer();
  ~LogicNodeFactoryContainer() override;

  [[nodiscard]] QString getName() const override;
  [[nodiscard]] QIcon getIcon() const override;
};

#endif//FLOW_LOGIC_NODE_FACTORY_CONTAINER_H
