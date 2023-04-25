#ifndef EGNITE_EXPORT_H
#define EGNITE_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(LIB_EGNITE_EXPORTS)
#define LIB_EGNITE_API Q_DECL_EXPORT
#else
#define LIB_EGNITE_API Q_DECL_IMPORT
#endif

#endif  // EGNITE_EXPORT_H
