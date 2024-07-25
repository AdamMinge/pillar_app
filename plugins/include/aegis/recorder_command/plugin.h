#ifndef AEGIS_SERVER_PLUGIN_H
#define AEGIS_SERVER_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

class RecorderCommandPlugin : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.flow.PluginInterface" FILE "plugin.json")

 public:
  explicit RecorderCommandPlugin();
  ~RecorderCommandPlugin() override;

  void init() override;
};

}  // namespace aegis

#endif  // AEGIS_SERVER_PLUGIN_H
