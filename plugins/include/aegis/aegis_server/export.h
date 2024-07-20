#ifndef AEGIS_SERVER_EXPORT_H
#define AEGIS_SERVER_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(AEGIS_SERVER_EXPORTS)
#define AEGIS_SERVER_API Q_DECL_EXPORT
#else
#define AEGIS_SERVER_API Q_DECL_IMPORT
#endif

#endif  // AEGIS_SERVER_EXPORT_H
