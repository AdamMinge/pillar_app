#ifndef LOGIC_GROUP_FACTORY_H
#define LOGIC_GROUP_FACTORY_H

/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/flow/factory/group_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class LOGIC_NODE_API LogicGroupFactory : public flow_document::GroupFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::GroupFactory);
  Q_PLUGIN_METADATA(IID "org.flow.LogicGroupFactory" FILE "plugin.json")

 public:
  explicit LogicGroupFactory();
  ~LogicGroupFactory() override;
};

#endif  // LOGIC_GROUP_FACTORY_H
