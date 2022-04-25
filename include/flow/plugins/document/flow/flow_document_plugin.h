#ifndef FLOW_FLOW_DOCUMENT_PLUGIN_H
#define FLOW_FLOW_DOCUMENT_PLUGIN_H

/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/plugin_interface.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FLOW_DOCUMENT_API FlowDocumentPlugin : public flow::PluginInterface
{
  Q_OBJECT
  Q_INTERFACES(flow::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

public:
  explicit FlowDocumentPlugin();
  ~FlowDocumentPlugin() override;

  void init() override;
};

#endif//FLOW_FLOW_DOCUMENT_PLUGIN_H
