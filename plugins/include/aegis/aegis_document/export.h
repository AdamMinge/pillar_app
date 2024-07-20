#ifndef AEGIS_DOCUMENT_EXPORT_H
#define AEGIS_DOCUMENT_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(AEGIS_DOCUMENT_EXPORTS)
#define AEGIS_DOCUMENT_API Q_DECL_EXPORT
#else
#define AEGIS_DOCUMENT_API Q_DECL_IMPORT
#endif

#endif  // AEGIS_DOCUMENT_EXPORT_H
