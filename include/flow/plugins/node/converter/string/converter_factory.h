#ifndef PLUGIN_FLOW_CONVERTER_FACTORY_PLUGIN_H
#define PLUGIN_FLOW_CONVERTER_FACTORY_PLUGIN_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/export.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/converter_factory.h>
/* -------------------------------------------------------------------------- */

namespace flow::node
{
  class Node;
}

class LOGIC_NODE_API StringConverterFactories : public flow::node::ConverterFactories
{
  Q_OBJECT
  Q_INTERFACES(flow::node::ConverterFactories);
  Q_PLUGIN_METADATA(IID "org.flow.ConverterFactories" FILE "plugin.json")

public:
  explicit StringConverterFactories();
  ~StringConverterFactories() override;
};

#endif//PLUGIN_FLOW_CONVERTER_FACTORY_PLUGIN_H
