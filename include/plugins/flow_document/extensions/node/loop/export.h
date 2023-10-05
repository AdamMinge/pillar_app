#ifndef EXPORT_H
#define EXPORT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtCore/QtGlobal>
/* -------------------------------------------------------------------------- */

#if defined(LOOP_NODE_EXPORTS)
#define LOOP_NODE_API Q_DECL_EXPORT
#else
#define LOOP_NODE_API Q_DECL_IMPORT
#endif

#endif  // EXPORT_H
