#ifndef FLOW_EXPORT_H
#define FLOW_EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(LIB_FLOW_EXPORTS)
#define LIB_FLOW_API Q_DECL_EXPORT
#else
#define LIB_FLOW_API Q_DECL_IMPORT
#endif

#endif  // FLOW_EXPORT_H
