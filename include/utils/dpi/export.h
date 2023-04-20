#ifndef UTILS_DPI_EXPORT_H
#define UTILS_DPI_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(DPI_EXPORTS)
#define DPI_API Q_DECL_EXPORT
#else
#define DPI_API Q_DECL_IMPORT
#endif

#endif  // UTILS_DPI_EXPORT_H
