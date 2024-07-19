#ifndef AEGIX_EXPORT_H
#define AEGIX_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(LIB_AEGIS_EXPORTS)
#define LIB_AEGIS_API Q_DECL_EXPORT
#else
#define LIB_AEGIS_API Q_DECL_IMPORT
#endif

#endif  // AEGIX_EXPORT_H
