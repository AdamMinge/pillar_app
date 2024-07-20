/* ----------------------------------- Local -------------------------------- */
#include "aegis_server/aegis_server_plugin.h"

#include "aegis_server/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <pillar/language_translator.h>
/* -------------------------------------------------------------------------- */

namespace aegis_server {

AegisServerPlugin::AegisServerPlugin() = default;

AegisServerPlugin::~AegisServerPlugin() = default;

void AegisServerPlugin::init() {
  addObject(
      new pillar::BaseLanguageTranslator(translations::TranslationsPath, this));
}

}  // namespace aegis_server