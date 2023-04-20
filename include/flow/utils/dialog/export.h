#ifndef UTILS_DIALOG_EXPORT_H
#define UTILS_DIALOG_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(DIALOG_EXPORTS)
#define DIALOG_API Q_DECL_EXPORT
#else
#define DIALOG_API Q_DECL_IMPORT
#endif

#endif  // UTILS_DIALOG_EXPORT_H
