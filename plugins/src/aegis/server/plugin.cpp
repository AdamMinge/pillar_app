/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/plugin.h"

#include "aegis/server/plugin_manager.h"
#include "aegis/server/resources.h"
#include "aegis/server/settings/server_settings_widget.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <pillar/language_translator.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

ServerPlugin::ServerPlugin() = default;

ServerPlugin::~ServerPlugin() { PluginManager::deleteInstance(); }

void ServerPlugin::init() {
  addObject(new ServerSettingsWidgetFactory(this));

  addObject(
      new pillar::BaseLanguageTranslator(translations::TranslationsPath, this));
}

}  // namespace aegis