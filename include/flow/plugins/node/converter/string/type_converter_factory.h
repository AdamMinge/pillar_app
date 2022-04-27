#ifndef PLUGIN_FLOW_TYPE_CONVERTER_FACTORY_PLUGIN_H
#define PLUGIN_FLOW_TYPE_CONVERTER_FACTORY_PLUGIN_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/node/type_converter_factory.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{
  class Node;
}

class LOGIC_NODE_API StringConverterFactories
    : public flow::node::TypeConverterFactories
{
  Q_OBJECT
  Q_INTERFACES(flow::node::TypeConverterFactories);
  Q_PLUGIN_METADATA(IID "org.flow.TypeConverterFactories" FILE "plugin.json")

public:
  explicit StringConverterFactories();
  ~StringConverterFactories() override;
};

#endif//PLUGIN_FLOW_TYPE_CONVERTER_FACTORY_PLUGIN_H
