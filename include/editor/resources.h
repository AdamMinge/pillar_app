#ifndef RESOURCES_H
#define RESOURCES_H

/* ------------------------------------- Qt --------------------------------- */
#include <QLatin1String>
/* -------------------------------------------------------------------------- */

/* ----------------------------------- Icons -------------------------------- */

namespace icons {

#define _DEFINE_ICON(name, size, icon) \
  constexpr QLatin1String name{":/editor/images/" size "/" icon};

namespace x16 {

_DEFINE_ICON(UndoClean, "16x16", "undo_clean.png")

}  // namespace x16

namespace x32 {

_DEFINE_ICON(ErrorIssue, "32x32", "error_issue.png")
_DEFINE_ICON(WarningIssue, "32x32", "warning_issue.png")

}  // namespace x32

namespace x64 {

_DEFINE_ICON(Project, "64x64", "project.png")
_DEFINE_ICON(UnknownDocument, "64x64", "unknown_document.png")

}  // namespace x64

namespace x256 {

_DEFINE_ICON(AboutLogo, "256x256", "about_logo.png")

}  // namespace x256

}  // namespace icons

/* -------------------------------- Translations ---------------------------- */

namespace translations {

constexpr QLatin1String TranslationsPath{":/editor/translations"};

}  // namespace translations

#endif  // RESOURCES_H
