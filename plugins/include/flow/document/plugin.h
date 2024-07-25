#ifndef FLOW_DOCUMENT_FLOW_DOCUMENT_PLUGIN_H
#define FLOW_DOCUMENT_FLOW_DOCUMENT_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_DOCUMENT_API DocumentPlugin : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit DocumentPlugin();
  ~DocumentPlugin() override;

  void init() override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_DOCUMENT_PLUGIN_H
