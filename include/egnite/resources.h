#ifndef EGNITE_RESOURCES_H
#define EGNITE_RESOURCES_H

/* ------------------------------------- Qt --------------------------------- */
#include <QLatin1String>
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Icons -------------------------------- */

namespace egnite {

namespace icons {

#define _DEFINE_ICON(name, size, icon) \
  constexpr QLatin1String name{":/egnite/images/" size "/" icon};

namespace x16 {

_DEFINE_ICON(UndoClean, "16x16", "undo_clean.png")

}  // namespace x16

namespace x64 {

_DEFINE_ICON(Plugin, "64x64", "plugin.png")

}  // namespace x64

}  // namespace icons

/* -------------------------------- Translations ---------------------------- */

namespace translations {

constexpr QLatin1String TranslationsPath{":/egnite/translations"};
constexpr QLatin1String QtTranslationsPrefix{"qt"};
constexpr QLatin1String EgniteTranslationsPrefix{"egnite"};

}  // namespace translations

}  // namespace egnite

#endif  // EGNITE_RESOURCES_H
