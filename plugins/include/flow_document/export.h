#ifndef FLOW_DOCUMENT_EXPORT_H
#define FLOW_DOCUMENT_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(FLOW_DOCUMENT_EXPORTS)
#define FLOW_DOCUMENT_API Q_DECL_EXPORT
#else
#define FLOW_DOCUMENT_API Q_DECL_IMPORT
#endif

#endif  // FLOW_DOCUMENT_EXPORT_H
