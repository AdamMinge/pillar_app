#ifndef UTILS_FILE_SYSTEM_EXPORT_H
#define UTILS_FILE_SYSTEM_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(FILE_SYSTEM_EXPORTS)
#define FILE_SYSTEM_API Q_DECL_EXPORT
#else
#define FILE_SYSTEM_API Q_DECL_IMPORT
#endif

#endif  // UTILS_FILE_SYSTEM_EXPORT_H
