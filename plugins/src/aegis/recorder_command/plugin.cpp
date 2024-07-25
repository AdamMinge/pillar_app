/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/aegis_server_plugin.h"
#include "aegis/server/resources.h"
#include "aegis/server/settings/server_settings_widget.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <pillar/language_translator.h>
/* -------------------------------------------------------------------------- */

namespace aegis {

AegisServerPlugin::AegisServerPlugin() = default;

AegisServerPlugin::~AegisServerPlugin() = default;

void AegisServerPlugin::init() {
  addObject(new ServerSettingsWidgetFactory(this));

  addObject(
      new pillar::BaseLanguageTranslator(translations::TranslationsPath, this));
}

}  // namespace aegis