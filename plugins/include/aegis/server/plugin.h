#ifndef AEGIS_SERVER_PLUGIN_H
#define AEGIS_SERVER_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class LIB_AEGIS_SERVER_API ServerPlugin : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit ServerPlugin();
  ~ServerPlugin() override;

  void init() override;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_PLUGIN_H
