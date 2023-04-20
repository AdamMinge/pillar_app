#ifndef UTILS_COLOR_EXPORT_H
#define UTILS_COLOR_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(COLOR_EXPORTS)
#define COLOR_API Q_DECL_EXPORT
#else
#define COLOR_API Q_DECL_IMPORT
#endif

#endif  // UTILS_COLOR_EXPORT_H
