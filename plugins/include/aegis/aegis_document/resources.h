#ifndef AEGIS_DOCUMENT_RESOURCES_H
#define AEGIS_DOCUMENT_RESOURCES_H

/* ------------------------------------- Qt --------------------------------- */
#include <QLatin1String>
/* ----------------------------------- Local -------------------------------- */
#include "aegis_document/export.h"
/* -------------------------------------------------------------------------- */

namespace aegis_document {

/* -------------------------------- Translations ---------------------------- */

namespace translations {

constexpr QLatin1String TranslationsPath{
    ":/plugins/aegis_document/translations"};

}  // namespace translations

}  // namespace aegis_document

#endif  // AEGIS_DOCUMENT_RESOURCES_H
