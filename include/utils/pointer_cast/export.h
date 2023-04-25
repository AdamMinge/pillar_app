#ifndef UTILS_POINTER_CAST_EXPORT_H
#define UTILS_POINTER_CAST_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(POINTER_CAST_EXPORTS)
#define POINTER_CAST_API Q_DECL_EXPORT
#else
#define POINTER_CAST_API Q_DECL_IMPORT
#endif

#endif  // UTILS_POINTER_CAST_EXPORT_H