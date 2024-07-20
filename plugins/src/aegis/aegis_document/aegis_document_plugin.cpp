/* ----------------------------------- Local -------------------------------- */
#include "aegis_document/aegis_document_plugin.h"
#include "aegis_document/resources.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <pillar/language_translator.h>
/* -------------------------------------------------------------------------- */

namespace aegis_document {

AegisDocumentPlugin::AegisDocumentPlugin() = default;

AegisDocumentPlugin::~AegisDocumentPlugin() = default;

void AegisDocumentPlugin::init() {
  addObject(
      new pillar::BaseLanguageTranslator(translations::TranslationsPath, this));
}

}  // namespace aegis_document