#ifndef AEGIS_OBJECT_COMMAND_PLUGIN_H
#define AEGIS_OBJECT_COMMAND_PLUGIN_H

/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/plugin_interface.h>
/* ---------------------------- Plugin Aegis Server ------------------------- */
#include <aegis/server/command/factory/utils.h>
/* ----------------------------------- Local -------------------------------- */
#include "aegis/object_command/command/dump_methods.h"
#include "aegis/object_command/command/dump_properties.h"
#include "aegis/object_command/command/invoke_method.h"
#include "aegis/object_command/command/set_property.h"
#include "aegis/object_command/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

class LIB_AEGIS_OBJECT_COMMAND_API ObjectCommandPlugin
    : public pillar::PluginInterface {
  Q_OBJECT
  Q_INTERFACES(pillar::PluginInterface)
  Q_PLUGIN_METADATA(IID "org.pillar.PluginInterface" FILE "plugin.json")

 public:
  explicit ObjectCommandPlugin();
  ~ObjectCommandPlugin() override;

  void init() override;
};

DECLARE_COMMAND_FACTORY(LIB_AEGIS_OBJECT_COMMAND_API, InvokeMethodCommand)
DECLARE_COMMAND_FACTORY(LIB_AEGIS_OBJECT_COMMAND_API, SetPropertyCommand)
DECLARE_COMMAND_FACTORY(LIB_AEGIS_OBJECT_COMMAND_API, DumpPropertiesCommand)
DECLARE_COMMAND_FACTORY(LIB_AEGIS_OBJECT_COMMAND_API, DumpMethodsCommand)

}  // namespace aegis

#endif  // AEGIS_OBJECT_COMMAND_PLUGIN_H
